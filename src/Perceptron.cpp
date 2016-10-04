#include "Perceptron.hpp"

#include <algorithm>
#include <cstdlib>

using namespace std;

Perceptron::Perceptron(unsigned int _inputSize) {
	for(unsigned int i = 0; i < _inputSize; ++i) {
		weights.push_back(initializeRandom());
	}

	bias = initializeRandom();
}

int Perceptron::computeOutput(vector<double> _inputs) {
	if(_inputs.size() != weights.size()) {
		//TODO: throw exception
		return 0;
	}

	double sum = 0.;
	for(unsigned int i = 0; i < weights.size(); ++i) {
		sum += weights[i] * _inputs[i];
	}
	sum += bias;

	return activation(sum);
}

void Perceptron::train(vector<vector<double>> _inputSet,
	vector<int> _outputSet, double _alpha, unsigned int _maxEpoch) {
	
	vector<unsigned int> indicies;
	for(unsigned int i = 0; i < weights.size(); ++i) {
		indicies.push_back(i);
	}

	for(unsigned int epochs = 0; epochs < _maxEpoch; ++epochs) {
		random_shuffle(indicies.begin(), indicies.end());

		for(unsigned int i = 0; i < _inputSet.size(); ++i) {
			int desired = _outputSet[i];
			int computed = computeOutput(_inputSet[i]);

			update(_inputSet[i], desired, computed, _alpha);
		}
	}
}

void Perceptron::update(vector<double> _inputs, int _desired,
	int _computed, double _alpha) {

	if(_desired == _computed)
		return;
	
	int delta = _computed - _desired;
	double factor = _alpha * delta;

	for(unsigned int i = 0; i < _inputs.size(); ++i) {
		if(_inputs[i] >= 0.) {
			weights[i] -= factor * _inputs[i];
		}
		else {
			weights[i] += factor * _inputs[i];
		}
	}

	bias -= factor;
}

int Perceptron::activation(double _value) {
	if(_value >= 0.)
		return 1;
	else
		return -1;
	
	//return (_value >= 0.) ? 1 : -1;
}

double Perceptron::initializeRandom() {
	return ((rand() % 10001) / 10000.) * (WEIGHT_MAX - WEIGHT_MIN)
			+ WEIGHT_MIN;
}
