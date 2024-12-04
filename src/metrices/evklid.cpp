#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double evklid(vector<double> p1, vector<double> p2){
      int size = p1.size();
      double sum = 0;
      for (int i = 0; i < size; i++){
            sum = sum + pow(p1[i] - p2[i], 2);
      };
      return pow(sum, 0.5);
};

int main(){
      vector<double> point1 = {3.5, 4.5, 5.5};
      vector<double> point2 = {4.5, 5.5, 6.5};
      cout << evklid(point1, point2);
      return 0;
}