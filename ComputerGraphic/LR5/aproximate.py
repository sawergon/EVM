import numpy as np
import matplotlib.pyplot as plt

m = 20
vertex = np.array([(0, 0) for _ in range(m)])
sz = 100
for i in range(m):
    x = np.random.randint(0, 100)
    y = np.random.randint(0, 100)
    vertex[i] = (x, y)
vertex_x = np.array([vertex[i][0] for i in range(m)], dtype="float")
print(vertex_x)
vertex_y = np.array([vertex[i][1] for i in range(m)], dtype="float")
print(vertex_y)


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
plt.plot(x, y, 'r')

new_x = [x[i] for i in range(0, len(x), 30)]
new_y = [y[i] for i in range(0, len(y), 30)]

plt.plot(new_x, new_y, 'b', linewidth=3)

plt.scatter(vertex_x, vertex_y, s=20)
plt.show()
