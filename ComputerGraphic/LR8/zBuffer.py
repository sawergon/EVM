from matplotlib import pyplot as plt
import numpy as np
import math
# class Point(object):
#     def __init__(self, x, y, z):
#         self.x = x
#         self.y = y
#         self.z = z
#
#     def __str__(self):
#         return "{0} {1} {2}".format(self.x, self.y, self.z)
#
#     def __copy__(self):
#         return Point(self.x, self.y, self.z)
#
#
# def Bresenham(start, end):
#     array = []
#     steep = abs(end.y - start.y) > abs(end.x - start.x)
#     if steep:
#         start.x, start.y = start.y, start.x
#         end.x, end.y = end.y, end.x
#     if start.x > end.x:
#         start.x, end.x = end.x, start.x
#         start.y, end.y = end.y, start.y
#         start.z, end.z = end.z, start.z
#
#     dx, dy = end.x - start.x, abs(end.y - start.y)
#     dx2, dy2 = dx + dx, dy + dy
#     d = -dx
#
#     if start.y < end.y:
#         y_step = 1
#     else:
#         y_step = -1
#
#     x = start.x
#     y = start.y
#
#     count = end.x - x + 1
#     dz = (end.z - start.z) / count
#
#     for x in range(start.x, end.x + 1):
#         xp, yp = (y, x) if steep else (x, y)
#         array.append((xp, yp, start.z))
#         start.z += dz
#
#         if d > 0:
#             y += y_step
#             d -= dx2
#
#         d += dy2
#
#     return array

def Bresenham(x0, y0, z0, x1, y1, z1):
    array = []
    steep = abs(y1 - y0) > abs(x1 - x0)
    if steep:
        x0, y0 = y0, x0
        x1, y1 = y1, x1
    if x0 > x1:
        x0, x1 = x1, x0
        y0, y1 = y1, y0
        z0, z1 = z1, z0

    dx, dy = x1 - x0, abs(y1 - y0)
    dx2, dy2 = dx + dx, dy + dy
    d = -dx

    if y0 < y1:
        y_step = 1
    else:
        y_step = -1

    x = x0
    y = y0

    count = x1 - x + 1
    dz = (z1 - z0) / count

    for x in range(x0, x1 + 1):
        xp, yp = (y, x) if steep else (x, y)
        array.append((xp, yp, z0))
        z0 += dz

        if d > 0:
            y += y_step
            d -= dx2

        d += dy2

    return array


def HorizontalBresenham(x0, x1, y, z0, z1):
    x_range = range(x0, x1 + 1)
    dz = (z1 - z0) / len(x_range)
    points = [(x, y, z0 + dz * (x - x0)) for x in x_range]

    return points


def ZBuffer(vertexes, vp, buff, color):
    get_min_x_by_y = dict()
    get_max_x_by_y = dict()
    x_y_to_z = np.full((s, s), -math.inf)
    for i in range(len(vertexes)):
        points = Bresenham(vertexes[i][0], vertexes[i][1], vertexes[i][2], vertexes[(i+1)%3][0], vertexes[(i+1)%3][1], vertexes[(i+1)%3][2])

        for x, y, z in points:
            x_y_to_z[y][x] = z
            if z > buff[y][x]:
                vp[y][x] = color
                buff[y][x] = z
            get_max_x_by_y[y] = max(get_max_x_by_y.get(y, -1), x)
            get_min_x_by_y[y] = min(get_min_x_by_y.get(y, float('inf')), x)

    for y, min_x, max_x in zip(get_max_x_by_y.keys(), get_min_x_by_y.values(), get_max_x_by_y.values()):
        z0, z1 = x_y_to_z[y][min_x], x_y_to_z[y][max_x]
        points = HorizontalBresenham(min_x, max_x, y, z0, z1)

        for x, y, z in points:
            if z > buff[y][x]:
                vp[y][x] = color
                buff[y][x] = z


s = 200
bg_clr = (255, 255, 255)

vp = np.full((s, s, 3), bg_clr)
buff = np.full((s, s), -math.inf)

vertexes = [(20, 10, 0), (140, 50, 0), (60, 70, -2)]
ZBuffer(vertexes, vp, buff, (0, 0, 255))

vertexes = [(10, 40, 0), (100, 10, 0), (120, 70, 0)]
ZBuffer(vertexes, vp, buff, (255, 0, 0))

plt.axis('off')
plt.imshow(vp)
plt.show()