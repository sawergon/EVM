import numpy as np
import matplotlib.pyplot as plt

background_color = (255, 255, 255)
# line_color = (0, 0, 0)
coef = 1
m = 7
vertex = np.array([(0, 20), (0, 40), (20, 40), (20, 20), (0, 0), (40, 0),
                   (20, 10)])
vertex_x = np.array([vertex[i][0] for i in range(m)], dtype="float")
print(vertex_x)
vertex_y = np.array([vertex[i][1] for i in range(m)], dtype="float")
print(vertex_y)
sz = 100


def xy(t, j):
    t1 = 1.0 - t
    t_m = [0.0 for _ in range(m)]
    t1_m = [0.0 for _ in range(m)]
    fact_m = [0.0 for _ in range(m)]
    t_m[0] = 1.0
    t1_m[0] = 1.0
    fact_m[0] = 1.0
    for i in range(1, m):
        t_m[i] = t_m[i - 1] * t
        t1_m[i] = t1_m[i - 1] * t1
        fact_m[i] = fact_m[i - 1] * i
    bt = 0.0
    for i in range(m):
        bt += fact_m[m - 1] / (fact_m[i] * fact_m[m - i - 1]) * t_m[i] * t1_m[m - i - 1] * vertex[i, j]
    return bt


space = np.linspace(0, 1, 50)
plt.plot(xy(space, 0), xy(space, 1), 'r')
plt.scatter(vertex_x, vertex_y, s=20)
plt.show()
