/*
 * ekf.h
 *
 *  Created on: Mar 21, 2018
 *      Author: alex
 */

#ifndef SRC_EKF_H_
#define SRC_EKF_H_

#include <Eigen/Dense>
#include "measurements.h"

class Ekf
{
public:
	void initialize(int num_landmarks, double motion_noise);
	void prediction(const Odometry& odom);

	Eigen::VectorXd mu;
	Eigen::MatrixXd Sigma;
	//motion noise
	Eigen::MatrixXd R;
	//sensor noise
	Eigen::MatrixXd Q;

};



#endif /* SRC_EKF_H_ */
