#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

void print_matrix(vector<vector<double>> matrix){
      for (vector<double> i : matrix){
            for (double j : i){
                  cout << j << " ";
            };
            cout << "\n";
      };
};

vector<vector<double>> create_matrix(vector<vector<double>> cl1, vector<vector<double>> cl2){
      vector<vector<double>> new_matrix;
      
      for (vector<double> i : cl1){
            i.push_back(1);
            new_matrix.push_back(i);
      };
      
      for (vector<double> i : cl2){
            i.push_back(1);
            for (int j = 0; j < i.size(); j++){
                  i[j] = -i[j];
            };
            new_matrix.push_back(i);
      };
      
      return new_matrix;
};

vector<vector<double>> transpose_matrix(vector<vector<double>> matrix){
      vector<vector<double>> new_matrix;
      int k_new_rows = matrix[0].size();
      vector<double> new_row;

      for (int i = 0; i < k_new_rows; i++){
            new_row = {};
            for (vector<double> j : matrix){
                  new_row.push_back(j[i]);
            };
            new_matrix.push_back(new_row);
      };

      return new_matrix;
};

vector<vector<double>> mult_matrices(vector<vector<double>> matrix1, vector<vector<double>> matrix2){
      vector<vector<double>> new_matrix;
      int matrix1_size = matrix1.size();
      int matrix2_size = matrix2.size();
      int chislo;
      vector<double> new_row;

      for (int i = 0; i < matrix1_size; i++){
            new_row = {};
            for (int j = 0; j < matrix1_size; j++){
                  chislo = 0;
                  for (int k = 0; k < matrix2_size; k++){
                        chislo = chislo + matrix1[i][k] * matrix2[k][j];
                  };
                  new_row.push_back(chislo);
            };
            new_matrix.push_back(new_row);
      };

      return new_matrix;
};

vector <vector <double>> getmatrixfordeter(int a, int b, vector <vector <double>> c) {
      vector <vector <double>> fin;
      vector <double> add;
      for (int i = 0; i < c.size(); i++) {
            add.clear();
            if (i == a) continue;
            for (int j = 0; j < c[0].size(); j++) {
                  if (j == b) continue;
                  add.push_back(c[i][j]);
            };
            fin.push_back(add);
      };
      return fin;
};

double determatrix(vector <vector <double>> a) {
      double b = 0;
      if (a.size() == 1) return a[0][0];
      if (a.size() == 2) return a[0][0] * a[1][1] - a[1][0] * a[0][1];
      for (int i = 0; i < a.size(); i++) {
            b = b + a[0][i] * determatrix(getmatrixfordeter(0, i, a)) * pow(-1, i);
      };   
      return b;
};

vector <vector <double>> matrix_dop(vector <vector <double>> a) {
      vector <vector <double>> b = a;
      for (int i = 0; i < a.size(); i++) {
            for (int j = 0; j < a[0].size(); j++) {
                  b[j][i] = pow(-1, i + j) * determatrix(getmatrixfordeter(i, j, a));
            };
      };    
      return b;
};

vector<vector<double>> mult_matrix_by_num(vector<vector<double>> matrix, double num){
      int rows = matrix.size();
      int tables = matrix[0].size();
      for (int i = 0; i < rows; i++){
            for (int j = 0; j < tables; j++){
                  matrix[i][j] = matrix[i][j] * num;
            };
      };
      return matrix;
};

vector<vector<double>> reverse_matrix(vector<vector<double>> matrix){
      double determinant = determatrix(matrix);
      vector<vector<double>> dop_matrix = matrix_dop(matrix);

      matrix = mult_matrix_by_num(dop_matrix, 1 / determinant);
      return matrix;
};

vector <vector <double>> fillyvector(int a, int d) {
      vector <vector <double>> b;
      vector <double> c;
      for (int i = 0; i < a; i++) {
            c.push_back(d);
            b.push_back(c);
            c.clear();
      };
      return b;
};

bool isnegative(vector <vector <double>> a) {
      bool b = false;
      for (int i = 0; i < a.size(); i++) {
            if (a[i][0] <= 0) b = true;
      };
      return b;
};

bool iszero(vector <vector <double>> a) {
      bool b = true;
      for (int i = 0; i < a.size(); i++) {
            if (a[i][0] != 0) b = false;
      };
      return b;
};

vector <vector <double>> Heavysidevector(vector <vector <double>> a) {
      for (int i = 0; i < a.size(); i++) {
            if (a[i][0] > 0) a[i][0] = 1;
            else a[i][0] = 0;
      };
      return a;
};

vector <vector <double>> vecplusvec(vector <vector <double>> a, vector <vector <double>> b) {
      for (int i = 0; i < a.size(); i++) a[i][0] = a[i][0] + b[i][0];
      return a;
}

vector <vector <double>> vecminusvec(vector <vector <double>> a, vector <vector <double>> b) {
      for (int i = 0; i < a.size(); i++) a[i][0] = a[i][0] - b[i][0];
      return a;
}

vector <vector <double>> vecmultmun(vector <vector <double>> a, double b) {
      for (int i = 0; i < a.size(); i++) a[i][0] = a[i][0] * b;
      return a;
};

vector <vector <double>> newy(vector <vector <double>> y, vector <vector <double>> a, double h) {
      vector <vector <double>> b, c, d, e;
      b = vecminusvec(a, y);
      c = Heavysidevector(b);
      d = vecmultmun(c, h);
      e = vecplusvec(y, d);
      return e;
};

vector<vector<double>> coshyap(vector<vector<double>> cl1, vector<vector<double>> cl2){
      vector<vector<double>> matrix;
      vector<vector<double>> t_matrix;
      vector<vector<double>> m_matrices;
      vector<vector<double>> psevdo_obr_m;
      vector<vector<double>> w;
      vector<vector<double>> vw;
      bool linearlyseparable = true;

      matrix = create_matrix(cl1, cl2);
      t_matrix = transpose_matrix(matrix);
      m_matrices = mult_matrices(t_matrix, matrix);
      psevdo_obr_m = reverse_matrix(m_matrices);
      
      vector <vector <double>> y = fillyvector(matrix.size(), 1);
      w = mult_matrices(psevdo_obr_m, y);
      vw = mult_matrices(matrix, w);   

      while (isnegative(vw)) {
            if ((iszero(Heavysidevector(vecminusvec(vw, y)))) and (not iszero(vecminusvec(vw, y)))) {
                  linearlyseparable = false;
                  break;
            };
            y = newy(vw, y, 0.5);
            w = mult_matrices(psevdo_obr_m, y);
            vw = mult_matrices(matrix, w);   
      };

      if (linearlyseparable) {
            print_matrix(w);
            return w;
      }
      else {
            return { {0} };
      };
};

int main(){
      vector<vector<double>> cl1;
      vector<vector<double>> cl2;
      vector<double> point1 = {1, 2};
      vector<double> point2 = {3, 4};
      vector<double> point3 = {5, 6};
      vector<double> point4 = {7, 8};
      vector<double> point5 = {9, 0};
      cl1.push_back(point1);
      cl1.push_back(point2);
      cl2.push_back(point3);
      cl2.push_back(point4);
      cl2.push_back(point5);
      coshyap(cl1, cl2);
      return 0;
}