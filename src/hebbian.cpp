#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <iomanip> // for setting precision

using namespace std;

// Sign function
int sgn(double x) {
  return (x > 0) ? 1 : ((x < 0) ? -1 : 0);
}

int main() {
  int numInputs = 2;
  vector<double> weights(numInputs + 1, 0.0);

  // Seed the random number generator for reproducibility (optional)
  random_device rd;
  mt19937 gen(rd());
  uniform_real_distribution<> dis(-1, 1); // Initialize with small random numbers

  cout << "Start weights: ";
  for (int i = 0; i < weights.size(); ++i) {
    weights[i] = dis(gen);
    cout << fixed << setprecision(3) << weights[i] << " "; //Fixed point output
  }
  cout << endl;

  // Training data 
  vector<pair<vector<double>, int>> trainingData = {
    {{10.0, 9.0}, -1}, 
    {{40.0, 26.0}, 1},  
    {{40.0, 77.0}, 1},  
    {{13.0, 9.0}, -1} 
  };
  int numExamples = trainingData.size();

  double learningRate = 0.01;
  bool converged = false;
  int maxEpochs = 1000;
  int epoch = 0;

  while (!converged && epoch < maxEpochs) {
    converged = true;
    for (int i = 0; i < numExamples; ++i) {
      vector<double> inputs = trainingData[i].first;
      int target = trainingData[i].second;
      inputs.insert(inputs.begin(), 1.0); // Add bias

      double weightedSum = 0;
      for (size_t j = 0; j < weights.size(); ++j) {
        weightedSum += inputs[j] * weights[j];
      }
      
      int prediction = sgn(weightedSum);
      
      if(prediction != target) {
        converged = false; //  Check for error after each training example
      }
       for (size_t j = 0; j < weights.size(); ++j){
        weights[j] += learningRate * (target - prediction) * inputs[j]; // Crucial update
      }
    }

    epoch++;

    // Print weights periodically (optional)
    if (epoch % 10 == 0) {
      cout << "Epoch " << epoch << ": ";
      for (double weight : weights) {
        cout << fixed << setprecision(3) << weight << " "; //Fixed point output
      }
      cout << endl;
    }
  }

  cout << "Learned weights: ";
  for (double weight : weights) {
    cout << fixed << setprecision(3) << weight << " "; //Fixed point output
  }
  cout << endl;
  cout << "Epochs: " << epoch << endl;

  return 0;
}