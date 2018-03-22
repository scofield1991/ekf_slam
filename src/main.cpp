#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include <vector>
#include <utility>

#include "ekf.h"
#include "measurements.h"


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
