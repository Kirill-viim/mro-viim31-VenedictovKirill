#include <iostream>
#include <vector>
#include <cmath> // For sigmoid function
#include <random> // For random weight initialization


using namespace std;

// Activation functions
double linear(double x) {
    return x;
}

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

int main() {
    // Training data (adjust as needed)
    vector<pair<vector<double>, double>> trainingData = {
        {{1.0, 0.0}, 1.0},    // Example 1
        {{0.0, 1.0}, 1.0},    // Example 2
        {{1.0, 1.0}, 0.0},    // Example 3
        {{0.0, 0.0}, 0.0}     // Example 4
    };

    // Number of inputs (excluding bias)
    int numInputs = trainingData[0].first.size();

    // Learning rate
    double learningRate = 0.1;

    // Number of epochs
    int numEpochs = 1000;

    // Choose activation function (0 for linear, 1 for sigmoid)
    int activationFunctionChoice = 1; // Set to 1 to use sigmoid
    auto activationFunction = (activationFunctionChoice == 0) ? linear : sigmoid;


    // Initialize weights (including bias) with small random values
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(-0.5, 0.5); //Distribution for initial weights

    vector<double> weights(numInputs + 1);
    for (int i = 0; i < weights.size(); ++i) {
        weights[i] = dist(gen);
        cout << "start weight " << i << " : " << weights[i] << endl;
    }


    // Hebbian learning
    for (int epoch = 0; epoch < numEpochs; ++epoch) {
        for (const auto& example : trainingData) {
            vector<double> inputs = example.first;
            double target = example.second;

            // Add bias input
            inputs.insert(inputs.begin(), 1.0);

            // Calculate weighted sum
            double weightedSum = 0.0;
            for (size_t i = 0; i < inputs.size(); ++i) {
                weightedSum += inputs[i] * weights[i];
            }

            // Calculate output
            double output = activationFunction(weightedSum);

            // Update weights (Hebbian rule)
            for (size_t i = 0; i < weights.size(); ++i) {
                weights[i] += learningRate * inputs[i] * target;
            }
        }
    }

    // Print learned weights
    cout << "Learned weights: ";
    for (double w : weights) {
        cout << w << " ";
    }
    cout << endl;

    return 0;
}