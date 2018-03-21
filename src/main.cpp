#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <vector>
#include <utility>

#include "ekf.h"


struct Landmark
{
	int id;
	int x;
	int y;
};

class Map
{
public:
	std::vector<Landmark> landmarks;

	void initialize_map(std::string path_to_map)
	{
		std::ifstream infile(path_to_map);

		std::string line;
		while(std::getline(infile, line))
		{
			std::istringstream iss(line);
			Landmark new_landmark;
			iss >> new_landmark.id >> new_landmark.x >> new_landmark.y;
			landmarks.push_back(std::move(new_landmark));
		}

	}
};

struct Odometry
{
	double rot_1;
	double trans;
	double rot_2;
};

struct Sensor
{
	int id;
	double range;
	double bearing;
};

struct Reading
{
	Odometry odometry;
	std::vector<Sensor> sensors;
};

class Measurements
{
public:
	std::vector<Reading> readings;
	void initialize(std::string path_to_measurements)
	{
		std::ifstream infile(path_to_measurements);
		std::string line;

		Reading new_read;
		bool first = true;

		while(std::getline(infile, line))
		{
			std::istringstream iss(line);
			std::string measure_type;
			iss >> measure_type;
			//std::cout << measure_type << "\n";

			if(measure_type == "ODOMETRY")
			{
				if(!first)
					readings.push_back(new_read);

				new_read.sensors = std::vector<Sensor>();

				Odometry new_odom;
				iss >> new_odom.rot_1 >> new_odom.trans >> new_odom.rot_2;
				new_read.odometry = new_odom;

				if(first)
					first = false;
			}
			if(measure_type == "SENSOR")
			{
				Sensor new_sensor;
				iss >> new_sensor.id >> new_sensor.range >> new_sensor.bearing;
				new_read.sensors.push_back(new_sensor);
			}

		}

		readings.push_back(new_read);

	};
};


int main(int argc, char** argv)
{
	if(argc != 3)
		std::cout << "Arguments should be provided: path/to/world.dat path/to/sensor.dat \n";

	std::string path_to_map = argv[1];
	std::string path_to_measurements = argv[2];

	Map map;
	map.initialize_map(path_to_map);

	Measurements measurements;
	measurements.initialize(path_to_measurements);

	for(auto landmark : map.landmarks)
	{
		std::cout << landmark.id << " " << landmark.x << " " << landmark.y << "\n";
	}

	for(auto reading : measurements.readings)
	{
		std::cout << "Odometry: " << reading.odometry.rot_1 << " " <<
				  reading.odometry.trans <<  " " << reading.odometry.rot_2 << "\n";

		for(auto sensor : reading.sensors)
		{
			std::cout << "Sensor: " << sensor.id << " " << sensor.range << " " << sensor.bearing << "\n";
		}

	}

	Ekf ekf_slam;
	ekf_slam.initialize(map.landmarks.size(), 0.1);

	return 0;
}
