import numpy as np
import matplotlib.pyplot as plt

background_color = (255, 0, 0)
sz = 100


class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y


vp = np.full((sz, sz, 3), background_color, dtype="uint8")
n = 0
while n < 10:
    w = np.random.randint(5, 10)
    h = np.random.randint(5, 10)
    x = np.random.randint(10, sz - w)
    y = np.random.randint(10, sz - h)

    if np.all(vp[y:y + h, x:x + w] == background_color):
        r = np.random.randint(0, 255)
        g = np.random.randint(0, 255)
        b = np.random.randint(0, 255)

        vp[y:y + h, x:x + w] = (r, g, b)
        n += 1

plt.axis("off")
path_color = (155, 155, 155)
start = Point(0, 0)
end = Point(0, 0)
marks_arr = np.full((sz, sz), -1)
while 1:
    start.x = np.random.randint(0, 20)
    start.y = np.random.randint(0, 20)
    end.x = np.random.randint(sz - 20, sz)
    end.y = np.random.randint(sz - 20, sz)
    if np.all(vp[start.x, start.y] == background_color) and np.all(vp[end.x, end.y] == background_color):
        break

vp[start.x, start.y] = path_color
vp[end.x, end.y] = path_color
p = Point(start.x, start.y)
print(start.x, start.y)
print(end.x, end.y)


def delt(x, y):
    return abs(end.x - x) + abs(end.y - y)


delta = end.x - start.x + end.y - start.y
for i in range(abs(end.x - start.x) + abs(end.y - start.y)):
    if p.x == end.x and p.y == end.y:
        break
    if p.y + 1 < sz and np.all(vp[p.x, p.y + 1] == background_color) and delt(p.x, p.y + 1) <= delta:
        delta = delt(p.x, p.y + 1)
        p.y = p.y + 1
        vp[p.x, p.y] = path_color
    elif p.x + 1 < sz and np.all(vp[p.x + 1, p.y] == background_color) and delt(p.x + 1, p.y) <= delta:
        delta = delt(p.x + 1, p.y)
        p.x = p.x + 1
        vp[p.x, p.y] = path_color
    elif 0 < p.y - 1 and np.all(vp[p.x, p.y - 1] == background_color) and delt(p.x, p.y - 1) <= delta:
        delta = delt(p.x, p.y - 1)
        p.y = p.y - 1
        vp[p.x, p.y] = path_color
    elif 0 < p.x - 1 and np.all(vp[p.x - 1, p.y] == background_color) and delt(p.x - 1, p.y) <= delta:
        delta = delt(p.x - 1, p.y)
        p.x = p.x - 1
        vp[p.x, p.y] = path_color

plt.imshow(vp)
plt.show()
