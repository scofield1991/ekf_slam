/*
 * ekf.cpp
 *
 *  Created on: Mar 21, 2018
 *      Author: alex
 */
#include "ekf.h"
#include  <Eigen/Dense>
#include <iostream>

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



