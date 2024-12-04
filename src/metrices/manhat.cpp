#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

double manhat(vector<double> p1, vector<double> p2){
      int size = p1.size();
      double sum = 0;
      for (int i = 0; i < size; i++){
            sum = sum + abs(p1[i] - p2[i]);
      };
      return sum;
};

int main(){
      vector<double> point1 = {3.5, 4.5, 5.5};
      vector<double> point2 = {4.5, 5.5, 6.5};
      cout << manhat(point1, point2);
      return 0;
}