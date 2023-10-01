import numpy as np
import matplotlib.pyplot as plt

background_color = (255, 255, 255)
line_color = (0, 0, 0)
sz = 20


class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return "{0} {1}".format(self.y, self.x)


vp = np.full((sz, sz, 3), background_color, dtype="uint8")


def distance(first, second):
    return np.sqrt((first.x - second.x) ** 2 + (first.y - second.y) ** 2)


def brezehemAlgWithInterpolation(start, end, space):
    steep = abs(end.y - start.y) > abs(end.x - start.x)
    r1 = 255
    r2 = 0
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
        t = distance(start, point) / dist
        if steep:
            xp, yp = point.y, point.x
        else:
            xp, yp = point.x, point.y
        space[xp, yp] = (1 - t) * r1 + t * r2
        d += dy2
        if d > 0:
            point.y += y_step
            d -= dx2
        point.x += 1


# a = Point(np.random.randint(0, sz - 1), np.random.randint(0, sz - 1))
# b = Point(np.random.randint(0, sz - 1), np.random.randint(0, sz - 1))
a = Point(0, 0)
b = Point(sz, sz)
print("start: ", a)
print("end:   ", b)

brezehemAlgWithInterpolation(a, b, vp)

# plt.axis("off")
plt.imshow(vp)
plt.show()
