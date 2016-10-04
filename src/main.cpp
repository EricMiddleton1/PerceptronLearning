#include <iostream>

#include "Perceptron.hpp"

using namespace std;

int main() {
	vector<vector<double>> inputSet = { {1.5, 2.0},
																			{2.0, 3.5},
																			{3.0, 5.0},
																			{3.5, 2.5},
																			{4.5, 5.0},
																			{5.0, 7.0},
																			{5.5, 8.0},
																			{6.0, 6.0} };
	vector<int> outputSet = {	-1,
														-1,
														-1,
														-1,
														1,
														1,
														1,
														1 };
	
	Perceptron percept(2);

	cout << "Starting perceptron training..." << endl;

	percept.train(inputSet, outputSet, 0.001, 100);

	cout << "Training complete.\n" << endl;

	cout << "Please enter space-separated normalized age and income values:"
		<< "\n>";

	while(1) {
		double age, income;

		cin >> age;
		cin >> income;

		int output = percept.computeOutput({age, income});

		cout << '\t' << output << "\n>";
	}
	

	return 0;
}
