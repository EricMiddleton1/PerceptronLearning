#pragma once

#include <vector>

class Perceptron
{
public:
	Perceptron(unsigned int);

	int computeOutput(std::vector<double>);

	void train(std::vector<std::vector<double>>, std::vector<int>,
		double, unsigned int);
private:
	const double WEIGHT_MIN = -0.01;
	const double WEIGHT_MAX = 0.01;

	void update(std::vector<double>, int, int, double);
	int activation(double);
	double initializeRandom();

	std::vector<double> weights;
	double bias;
};
