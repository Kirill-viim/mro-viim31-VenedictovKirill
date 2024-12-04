import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import math

#Считывание данных об образах из файла
file_data = open("data.txt")
k_class = int(file_data.readline())
k_points_class = [int(i) for i in file_data.readline().split(" ")]
k_izm = int(file_data.readline())
# Построение графика
fig, ax = plt.subplots()
plt.axhline(0,color='black',linewidth=1)
plt.axvline(0,color='black',linewidth=1)
plt.grid(color='gray',linestyle='--',linewidth=0.5)
#Черчение прямоугольников
for i in range(k_class):
      s_ranges = []
      min_ranges = []
      max_ranges = []
      s_ranges = [int(i) for i in file_data.readline().split(" ")]
      min_ranges = s_ranges[:int(len(s_ranges)/2)]
      max_ranges = s_ranges[int(len(s_ranges)/2):]
      width = max_ranges[0] - min_ranges[0]
      height = max_ranges[1] - min_ranges[1]
      ax.add_patch(Rectangle((min_ranges[0], min_ranges[1]), width, height, facecolor = 'gray'))
file_data.close()
#Черечение линий между образами
file_hokashyap = open("Hokashyap.txt")
while True:
      koefs = [float(i) for i in file_hokashyap.readline().split()]
      if koefs == []:
            break
      file_data = open("data.txt")
      for i in range(3):
            file_data.readline()
      coords = []
      if abs(koefs[0] / koefs[1]) < 1:
            x_min_coords = []
            x_max_coords = []
            for i in range(k_class):
                  coords = [float(i) for i in file_data.readline().split()]
                  x_min_coords.append(coords[0])
                  x_max_coords.append(coords[k_izm])
            x = []
            y = []
            x.append(min(x_min_coords) - 0.1 * (max(x_max_coords) - min(x_min_coords)))
            x.append(max(x_max_coords) + 0.1 * (max(x_max_coords) - min(x_min_coords)))
            y.append((-koefs[2] - koefs[0]*x[0])/koefs[1])
            y.append((-koefs[2] - koefs[0]*x[1])/koefs[1])
            ax.plot(x, y, color = "m")
      else:
            y_min_coords = []
            y_max_coords = []
            for i in range(k_class):
                  coords = [float(i) for i in file_data.readline().split()]
                  y_min_coords.append(coords[1])
                  y_max_coords.append(coords[k_izm + 1])
            x = []
            y = []
            y.append(min(y_min_coords) - 0.1 * (max(y_max_coords) - min(y_min_coords)))
            y.append(max(y_max_coords) + 0.1 * (max(y_max_coords) - min(y_min_coords)))
            x.append((-koefs[2] - koefs[1]*y[0])/koefs[0])
            x.append((-koefs[2] - koefs[1]*y[1])/koefs[0])
            ax.plot(x, y, color = "m")
      file_data.close()
file_hokashyap.close()
#Изображение элементов образов
file_points = open("file_for_drawing.txt")
x = []
y = []
for k_points in k_points_class:
      file_points.readline()
      for i in range(k_points):
            points = [float(i) for i in file_points.readline().split(" ") if i!="\n"]
            x.append([points[0]])
            y.append([points[1]])
plt.scatter(x, y, c = "blue", s = 10)
file_points.close()
# Изображение первоначальных центроидов
file_centroids = open("start_centroids.txt")
x = []
y = []
k_centroids = int(file_centroids.readline())
for i in range(k_centroids):
      points = [float(j) for j in file_centroids.readline().split(" ") if j!="\n"]
      x.append(points[0])
      y.append(points[1])
plt.scatter(x, y, c = "orange", s = 2)
file_centroids.close()
# Изображение итоговых центроидов
file_centroids = open("k_means.txt")
x = []
y = []
k_centroids = int(file_centroids.readline())
for i in range(k_centroids):
      points = [float(j) for j in file_centroids.readline().split(" ") if j!="\n"]
      x.append(points[0])
      y.append(points[1])
plt.scatter(x, y, c = "orange", s = 15)
file_centroids.close()

# Изображение редактированных центроидов
file_r_centroids = open("redacted_centroids.txt")
x = []
y = []
k_centroids = int(file_r_centroids.readline())
for i in range(k_centroids):
      points = [float(j) for j in file_r_centroids.readline().split(" ") if j!="\n"]
      x.append(points[0])
      y.append(points[1])
plt.scatter(x, y, c = "green", s = 15)
file_r_centroids.close()

plt.show()