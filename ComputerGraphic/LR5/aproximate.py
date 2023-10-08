import numpy as np
import matplotlib.pyplot as plt

background_color = (255, 255, 255)
line_color = np.array((0, 0, 0))
m = 8
vertex = np.array([(0, 0) for _ in range(m)])
sz = 200
coef = int(sz / 100)
vertex[0] = (np.random.randint(0, 10), np.random.randint(0, 10))
for i in range(1, m):
    vertex[i] = (np.random.randint(vertex[i - 1][0], vertex[i - 1][0] + 20),
                 np.random.randint(vertex[i - 1][1], vertex[i - 1][1] + 20))
vertex_x = np.array([vertex[i][0] * coef for i in range(m)], dtype="float")
print(vertex_x)
vertex_y = np.array([vertex[i][1] * coef for i in range(m)], dtype="float")
print(vertex_y)


class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return "{0} {1}".format(self.y, self.x)


# def xy(i, t, j):
#     t0 = t - i
#     t02 = t0 * t0
#     t03 = t02 * t0
#     t1 = 1.0 - t0
#     t12 = t1 * t1
#     t13 = t12 * t1
#     return (t13 * vertex[i, j] + (3 * t03 - 6 * t02 + 4) * vertex[1 + i, j] + (-3 * t03 + 3 * t02 + 3 * t0 + 1) *
#             vertex[2 + i, j] + t03 * vertex[3 + i, j]) / 6.0

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


def draw_vertex(point, space, color, size=1):
    sz = size - size // 2 - size // 4
    for i in range(point.x - 2 - sz, point.x + 2 + sz):
        for j in range(point.y - 2 - sz, point.y + 2 + sz):
            space[i][j] = color


def distance(first, second):
    return np.sqrt((first.x - second.x) ** 2 + (first.y - second.y) ** 2)


def colored_col(space, x, y, size, color):
    for i in range(size):
        space[x][y+i] = color


def brezehemAlg(start, end, space, is_colored=False, size=1):
    global line_color
    if is_colored:
        new_line_color = np.array((np.random.randint(0, 255), np.random.randint(0, 255), np.random.randint(0, 255)))
    else:
        line_color = (0, 0, 0)
    steep = abs(end.y - start.y) > abs(end.x - start.x)
    if is_colored:
        draw_vertex(end, space, new_line_color, size)
    else:
        draw_vertex(end, space, line_color, size)
    if steep:
        start.x, start.y = start.y, start.x
        end.x, end.y = end.y, end.x
    if start.x > end.x:
        start.x, end.x = end.x, start.x
        start.y, end.y = end.y, start.y
    dx = end.x - start.x
    dy = end.y - start.y
    dx2 = 2 * dx
    dy2 = 2 * dy
    d = -dx
    y_step = 1 if start.y < end.y else -1
    point = Point(start.x, start.y)
    dist = distance(start, end)
    while point.x < end.x:
        if steep:
            xp, yp = point.y, point.x
        else:
            xp, yp = point.x, point.y
        if is_colored:
            t = distance(start, point) / dist
            color = (1 - t) * line_color + t * new_line_color
            colored_col(space, xp, yp, size, color)
        else:
            colored_col(space, xp, yp, size, line_color)
        d += dy2
        if d > 0:
            point.y += y_step
            d -= dx2
        point.x += 1
    if is_colored:
        line_color = new_line_color


t = 0.0
dt = 0.01
x = []
y = []
while t <= 1.01:
    x.append(xy(t, 0) * coef)
    y.append(xy(t, 1) * coef)
    t += dt
plt.plot(x, y, 'r')

new_x = [x[i] for i in range(0, len(x), 10)]
new_y = [y[i] for i in range(0, len(y), 10)]

print(new_x)
print(new_y)
vp = np.full((sz, sz, 3), background_color, dtype="uint8")


line_color = np.array((np.random.randint(0, 255), np.random.randint(0, 255), np.random.randint(0, 255)))
sz = 4
draw_vertex(Point(int(new_y[0]), int(new_x[0])), vp, line_color, sz)
for i in range(len(new_y) - 1):
    brezehemAlg(Point(int(new_y[i]), int(new_x[i])),
                Point(int(new_y[i + 1]), int(new_x[i + 1])), vp, True, sz)

# plt.plot(new_x, new_y, 'b', linewidth=1)

# plt.scatter(new_x, new_y)
plt.scatter(vertex_x, vertex_y, s=20)
plt.imshow(vp)
plt.show()
plt.imshow(vp)
# plt.scatter(new_x, new_y)
plt.show()
