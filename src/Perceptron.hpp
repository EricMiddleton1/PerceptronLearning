#pragma once

#include <vector>
#include <functional>
#include <fstream>

class Perceptron
{
public:
	Perceptron(unsigned int);

	void setActivationFunction(const std::function<int(double)>&);
	
	int computeOutput(const std::vector<double>&) const;

	void train(const std::vector<std::vector<double>>&, const std::vector<int>&,
		double, unsigned int);
private:
	const double WEIGHT_MIN = -0.01;
	const double WEIGHT_MAX = 0.01;

	void update(const std::vector<double>&, int, int, double);
	double initializeRandom() const;

	void writeState(std::ofstream& file) const;

	std::vector<double> weights;
	double bias;

	std::function<int(double)> activation;
};
