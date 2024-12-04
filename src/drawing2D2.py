import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, Circle
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
#Черчение кругов и тд
file_rounds = open("forel.txt")
r = float(file_rounds.readline())
x = []
y = []
x_centres = []
y_centres = []
while True:
      s = file_rounds.readline()
      if s == '':
            break
      if s == "next round\n":
            plt.scatter(x, y, s = 10)
            x = []
            y = []
            s = [float(i) for i in file_rounds.readline().split() if i!="\n"]
            x_centres.append(s[0])
            y_centres.append(s[1])
      else:
            s = [float(i) for i in s.split() if i!="\n"]
            x.append(s[0])
            y.append(s[1])
            
for i in range(len(x_centres)):
      ax.add_patch(Circle((x_centres[i], y_centres[i]), r, fc = 'white', ec = 'red', alpha = 0.6))
plt.scatter(x_centres, y_centres, c = "red", s = 20)
file_rounds.close()
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


plt.show()