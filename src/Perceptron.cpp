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

void Perceptron::setActivationFunction(const std::function<int(double)>&
	_activationFunction) {

	activation = _activationFunction;
}

int Perceptron::computeOutput(const vector<double>& _inputs) const {
	if(_inputs.size() != weights.size() || !activation) {
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

void Perceptron::train(const vector<vector<double>>& _inputSet,
	const vector<int>& _outputSet, double _alpha, unsigned int _maxEpoch) {

	ofstream outputFile("PerceptronState.csv");
	outputFile << "Interation";
	for(unsigned int i = 0; i < weights.size(); ++i)
		outputFile << ", weight" << i;
	
	outputFile << ", bias\n";

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

		outputFile << epochs << ", ";
		writeState(outputFile);
	}
}

void Perceptron::update(const vector<double>& _inputs, int _desired,
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

double Perceptron::initializeRandom() const {
	return ((rand() % 10001) / 10000.) * (WEIGHT_MAX - WEIGHT_MIN)
			+ WEIGHT_MIN;
}

void Perceptron::writeState(ofstream& file) const {
	for(unsigned int i = 0; i < weights.size(); ++i)
		file << weights[i] << ", ";
	
	file << bias << '\n';
}
