#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

// Задаем глобальные переменные
int class_k;
int k_izm;

struct ClassParams{
    int k_izm;
    vector<double> min_ranges;
    vector<double> max_ranges;

    ClassParams(int k, vector<double> min, vector<double> max){
        k_izm = k;
        min_ranges = min;
        max_ranges = max;
    };
};

class ClassParamsRepository{
    public:
    vector<ClassParams> repository;
    vector<int> structs_k_elements;

    ClassParamsRepository(string file_for_struct_generating){
        // Открываем файл для считывания
        ifstream file(file_for_struct_generating);
        // Считываем количество классов
        string s;
        getline(file, s);
        class_k = stoi(s);

        // Считываем количесвто элементов для каждого класса
        getline(file, s);
        stringstream ss(s);
        string k;
        while (ss >> k){
            structs_k_elements.push_back(stoi(k));
        };

        // Считываем количество измерений
        getline(file, s);
        k_izm = stoi(s);

        // Считываем ограничения классов, создаем структуры и заносим их в репозиторий
        vector<double> min_points_ranges;
        vector<double> max_points_ranges;
        for (int i = 0; i < class_k; i++){
            getline(file ,s);
            int n = 0;
            min_points_ranges={};
            max_points_ranges={};
            string p = "";
            stringstream ss(s);
            while (ss >> p){
                if (n < k_izm) min_points_ranges.push_back(stoi(p));
                else max_points_ranges.push_back(stoi(p));
                n++;
            };
            // Заносим в репозиторий
            repository.push_back(ClassParams(k_izm, min_points_ranges, max_points_ranges));
        };
        // Закрываем файл считывания
        file.close();
    };
};

struct Points_For_One_Struct{
    vector<vector<double>> points;
};

class Points_For_All_Classes{
    public:
    vector<Points_For_One_Struct> points_repository;

    void generate_points_for_one_struct(ClassParamsRepository repos, int n){
        ClassParams strukt = repos.repository[n];
        int n_k_points = repos.structs_k_elements[n];
        vector<double> s;
        Points_For_One_Struct pfos;
        for (int i = 0; i < n_k_points; i++){
            s = {};
            for (int i = 0; i < strukt.k_izm; i++){
                int start = strukt.min_ranges[i];
                int end = strukt.max_ranges[i];
                float x = rand() % ((end - start)*100 + 1) / 100.0 + start;
                s.push_back(x);
            };
            pfos.points.push_back(s);
        };
        points_repository.push_back(pfos);
    };

    void transit_points_for_one_struct(string file_to_transit, int n_class){
        ofstream file;
        file.open(file_to_transit, ios::app);
        file << "Класс " << to_string(n_class + 1) << "\n";
        vector<vector<double>> points_vector = points_repository[n_class].points;
        for (vector<double> i : points_vector){
            for (int j = 0; j < k_izm; j++){
                file << to_string(i[j]) << " ";
            };
            file << "\n";
        };
        file.close();
    };

    vector<double> find_center(ClassParamsRepository repos, int n){
        vector<vector<double>> points_vector = points_repository[n].points;
        double n_k_points = repos.structs_k_elements[n];
        vector<double> center;
        double sum;

        for (int i = 0; i < k_izm; i++){
            sum = {};
            for (int j = 0; j < n_k_points; j++){
                sum = sum + points_vector[j][i];
            };
            double avg = sum / n_k_points;
            center.push_back(avg);
        };
        return center;
    };
};

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
      double chislo;
      vector<double> new_row;

      for (int i = 0; i < matrix1.size(); i++){
            new_row = {};
            for (int j = 0; j < matrix2[0].size(); j++){
                  chislo = 0;
                  for (int k = 0; k < matrix2.size(); k++){
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

void transit_coshyap(string file_to_transit, vector <vector <double>> vector_to_transit){
      ofstream out;
      out.open(file_to_transit);
      for (int i = 0; i < vector_to_transit.size(); i++){
            out << vector_to_transit[i][0] << " ";
      };
      out.close();
};

vector<vector<double>> coshyap(Points_For_All_Classes repos, int n_cl1, int n_cl2){
      vector<vector<double>> matrix;
      vector<vector<double>> t_matrix;
      vector<vector<double>> m_matrices;
      vector<vector<double>> obr_m;
      vector<vector<double>> psevdo_obr_m;
      vector<vector<double>> w;
      vector<vector<double>> vw;
      bool linearlyseparable = true;

      vector<vector<double>> cl1 = repos.points_repository[n_cl1].points;
      vector<vector<double>> cl2 = repos.points_repository[n_cl2].points;
      matrix = create_matrix(cl1, cl2);
      t_matrix = transpose_matrix(matrix);
      m_matrices = mult_matrices(t_matrix, matrix);
      obr_m = reverse_matrix(m_matrices);
      psevdo_obr_m = mult_matrices(obr_m, t_matrix);

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
            transit_coshyap("Hokashyap.txt", w);
            return w;
      }
      else {
            return { {0} };
      };
};

double evklid(vector<double> p1, vector<double> p2){
      int size = p1.size();
      double sum = 0;
      for (int i = 0; i < size; i++){
            sum = sum + pow(p1[i] - p2[i], 2);
      };
      return pow(sum, 0.5);
};

double manhat(vector<double> p1, vector<double> p2){
      int size = p1.size();
      double sum = 0;
      for (int i = 0; i < size; i++){
            sum = sum + abs(p1[i] - p2[i]);
      };
      return sum;
};

int main()
{
    // Создаем класс для хранения образов
    ClassParamsRepository rep("data.txt");
    // Создаем репозиторий точек
    Points_For_All_Classes points_rep;
    // Генерация точек и ввод в текстовый файл
    for (int i = 0; i < class_k; i++){
        points_rep.generate_points_for_one_struct(rep, i);
    };
    // Очищаем файл, в который будем заносить точки
    ofstream file;
    file.open("file_for_drawing.txt");
    file.clear();
    // Заносим точки в файл
    for (int i = 0; i < class_k; i++){
        points_rep.transit_points_for_one_struct("file_for_drawing.txt", i);
    };
    // Находим центры классов
    //vector<double> center1 = points_rep.find_center(rep, 0);
    //vector<double> center2 = points_rep.find_center(rep, 1);
    //for (double i : center1){
    //    cout << i << endl;
    //};
    //for (double i : center2){
    //    cout << i << endl;
    //};
    // Находим метрики
    // cout << evklid(center1, center2) << endl;
    // cout << manhat(center1, center2);
    // Кошьяпчик
    vector<vector<double>> lin_fun = coshyap(points_rep, 0, 1);

}