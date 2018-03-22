/*
 * ekf.cpp
 *
 *  Created on: Mar 21, 2018
 *      Author: alex
 */
#include "ekf.h"
#include  <Eigen/Dense>
#include <iostream>
#include  <math.h>

using Eigen::MatrixXd;
using Eigen::VectorXd;

int INF = 10000;

void Ekf::initialize(int num_landmarks, double motion_noise)
{
	int dim = 3+2*num_landmarks;
	mu = VectorXd::Zero(dim);
	Sigma = MatrixXd::Identity(dim, dim)*0.01;
	Sigma.bottomRightCorner(2*num_landmarks, 2*num_landmarks) *= INF;

	std::cout << Sigma << "\n";

	R = MatrixXd::Identity(3, 3) * motion_noise;
	R(2,2) /= 10;

	std::cout << R << "\n";

}

void Ekf::prediction(const Odometry& odom)
{
	Eigen::Vector3d temp_mu = mu.head(3);

	auto x_transform = odom.trans * cos(temp_mu(2) + odom.rot_1);
	auto y_transform = odom.trans * sin(temp_mu(2) + odom.rot_1);
	auto angle_transform = odom.rot_1 + odom.rot_2;

	temp_mu(0) = temp_mu(0) + x_transform;
	temp_mu(1) = temp_mu(1) + y_transform;
	temp_mu(2) = temp_mu(2) + angle_transform;

	mu.head(3) = temp_mu;



}





