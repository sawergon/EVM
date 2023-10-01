import numpy as np
import matplotlib.pyplot as plt

background_color = (255, 255, 255)
coef = 1
m = 11
vertex = np.array([(0, 60), (10, 80), (30, 80), (40, 60), (50, 10), (60, 0),
                   (75, 30), (80, 70), (0, 60), (10, 80), (30, 80)])
vertex_x = np.array([vertex[i][0] for i in range(m)], dtype="float")
print(vertex_x)
vertex_y = np.array([vertex[i][1] for i in range(m)], dtype="float")
print(vertex_y)
sz = 100



def xy(i, t, j):
    t0 = t - i
    t02 = t0 * t0
    t03 = t02 * t0
    t1 = 1.0 - t0
    t12 = t1 * t1
    t13 = t12 * t1
    return (t13 * vertex[i, j] + (3 * t03 - 6 * t02 + 4) * vertex[1 + i, j] + (-3 * t03 + 3 * t02 + 3 * t0 + 1) *
            vertex[2 + i, j] + t03 * vertex[3 + i, j]) / 6.0


t = 0.0
dt = 0.02
x = []
y = []

for i in range(0, m - 3):
    t = i
    while t <= i + 1:
        x.append(xy(i, t, 0))
        y.append(xy(i, t, 1))
        t += dt
    # space = np.linspace(0, i + 1, int((i + 1) / dt))
plt.plot(x, y, 'r')
plt.scatter(vertex_x, vertex_y, s=20)
plt.show()
