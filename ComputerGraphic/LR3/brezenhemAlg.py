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


def brezehemAlg(start, end, space):
    steep = abs(end.y - start.y) > abs(end.x - start.x)
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
    while point.x < end.x:
        if steep:
            xp, yp = point.y, point.x
        else:
            xp, yp = point.x, point.y
        space[xp, yp] = line_color
        d += dy2
        if d > 0:
            point.y += y_step
            d -= dx2
        point.x += 1


# a = Point(np.random.randint(0, sz - 1), np.random.randint(0, sz - 1))
# b = Point(np.random.randint(0, sz - 1), np.random.randint(0, sz - 1))
a = Point(5, 5)
b = Point(10, 10)
print("start: ", a)
print("end:   ", b)

brezehemAlg(a, b, vp)

# plt.axis("off")
plt.imshow(vp)
plt.show()
