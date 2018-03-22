/*
 * Measurements.h
 *
 *  Created on: Mar 21, 2018
 *      Author: alex
 */

#ifndef SRC_MEASUREMENTS_H_
#define SRC_MEASUREMENTS_H_

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


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



#endif /* SRC_MEASUREMENTS_H_ */
