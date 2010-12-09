/**
	@file kftest.cpp
	@brief

	@date 2010

	@author
	Ryan Pavlik
	<rpavlik@iastate.edu> and <abiryan@ryand.net>
	http://academic.cleardefinition.com/
	Iowa State University Virtual Reality Applications Center
	Human-Computer Interaction Graduate Program
*/

// Internal Includes
// - none

// Library/third-party includes
#include <eigenkf/KalmanFilter.h>

// Standard includes
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>

using namespace eigenkf;

#define COL 10

double noise() {
	return (std::rand() % 10) / 10.0 - 0.5;
}

int main(int argc, char * argv[]) {
	std::srand(std::time(NULL));
	typedef SimpleState<2> state_t;
	typedef ConstantProcess<2, state_t> process_t;
	KalmanFilter<state_t, process_t> kf;
	kf.processModel.sigma = state_t::VecState::Constant(0.5);
	double dt = 0.5;
	std::cout << "actual,measurement,filtered" << std::endl;
	for (double t = 0; t < 50.0; t+= dt) {
		kf.predict(dt);

		Eigen::Vector2d pos(Eigen::Vector2d::Constant(t));
		AbsoluteMeasurement<state_t> meas;
		meas.measurement = (pos + Eigen::Vector2d(noise(), noise())).eval();
		meas.covariance = Eigen::Vector2d::Constant(0.25).asDiagonal();
		kf.correct(meas);
		/*
		std::cout << std::setw(COL) << (kf.state.x - pos).norm();
		std::cout << std::setw(COL) << kf.state.x[0] << "," << std::setw(COL) << kf.state.x[1];
		std::cout << std::setw(COL) << "Actual: ";
		std::cout << std::setw(COL) << pos[0] << "," << std::setw(COL) << pos[1] << std::endl;;
		*/
		std::cout << pos[0] << "," << meas.measurement[0] << "," << kf.state.x[0] << std::endl;
		
	}
	return 0;

}
