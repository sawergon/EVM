import matplotlib.pyplot as plt
import matplotlib.patches
import numpy as np


class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return "{0} {1}".format(self.y, self.x)


# Класс треугольного полигона
class Polygon:
    def __init__(self, A, B, C):
        self.A = A
        self.B = B
        self.C = C

    def is_inside(self, P):
        exp1 = (self.A.x - P.x) * (self.B.y - self.A.y) - (self.B.x - self.A.x) * (self.A.y - P.y)
        exp2 = (self.B.x - P.x) * (self.C.y - self.B.y) - (self.C.x - self.B.x) * (self.B.y - P.y)
        exp3 = (self.C.x - P.x) * (self.A.y - self.C.y) - (self.A.x - self.C.x) * (self.C.y - P.y)
        if (exp1*exp2 > 0 and exp1*exp3 > 0):
            return True
        return False

def distance(first, second):
    return np.sqrt((first.x - second.x) ** 2 + (first.y - second.y) ** 2)


def what_color(rA, rB, rC, A, B, C, P):
    kCP = (C.y - P.y) / (C.x - P.x)
    if (B.x - A.x) == 0:
        xm = A.x
    else:
        kAB = (B.y - A.y) / (B.x - A.x)
        xm = ((C.y - A.y) + A.x * kAB - C.x * kCP) / (kAB - kCP)
    ym = C.y + (xm - C.x) * kCP
    M = Point(xm, ym)
    t = distance(A, M) / distance(A, B)
    colorM = (1 - t) * rA + t * rB
    t = distance(M, P) / distance(M, C)
    colorP = (1 - t) * colorM + t * rC
    res = list(colorP)
    for i in range(3):
        res[i] = 255 if int(res[i]) >= 255 else int(res[i])
    return tuple(res)

background_color = (np.random.randint(0, 255), np.random.randint(0, 255), np.random.randint(0, 255))
color = (np.random.randint(0, 255), np.random.randint(0, 255), np.random.randint(0, 255))
sz = 400
vp = np.full((sz, sz, 3), background_color, dtype="uint8")
rA = np.array([255, 0, 0])
rB = np.array([0, 255, 0])
rC = np.array([0, 0, 255])
A = Point(50, 50)
B = Point(50, 350)
C = Point(350, 50)
pol = Polygon(A, B, C)
for i in range(sz):
    for j in range(sz):
        p = Point(i, j)
        if (pol.is_inside(p)):
            vp[i, j] = color
# print(vp)
plt.imshow(vp)
plt.show()
for i in range(sz):
    for j in range(sz):
        p = Point(i, j)
        if (pol.is_inside(p)):
            vp[i, j] = what_color(rA, rB, rC, A, B, C, p)
# print(vp)
plt.imshow(vp)
plt.show()
# fig, ax = plt.subplots()
# fv = np.array([(22, 227), (150, 164), (277, 227), (150, 291)])
# plg = plt.Polygon(fv, color = 'm', fill = False) # fill = True
# ax.add_patch(plg)
# fv = [(v[0], v[1] - 150) for v in fv]
# plg = plt.Polygon(fv, color = 'g')
# ax.add_patch(plg)
# ax.set_xlim(0, 300); ax.set_ylim(0, 300)
# plt.axis('off')
# plt.show()
#
#
# W = H = 64 # Размер текстуры равен H * W
# img = np.zeros((H, W, 3), dtype = 'uint8')
# for i in range(H): # Генерация черно-белой карты текстуры
#     for j in range(W):
#         img[i, j, :] = (i & 16 ^ j & 16) * 255
# plt.axis('off')
# plt.imshow(img)
# plt.show()
#
# img = np.full((H, W, 3), 200, dtype = 'uint8')
# img[:16, 16:32, :2] = 0   # (0, 0, 200)
# img[:16, 48:, 2:] = 0     # (200, 0, 0)
# img[16:32, :16, 0] = 0    # (0, 200, 200)
# img[16:32, 32:48, 1] = 0  # (200, 0, 200)
# img[32:48, 16:32, 2] = 0  # (200, 200, 0)
# img[32:48, 48:, 0] = 0    # (0, 200, 200)
# img[32:48, 48:, 2] = 0    # (0, 200, 0)
# img[48:, :16, :2] = 100   # (100, 100, 200)
# img[48:, 32:48, 2:] = 100 # (200, 100, 100)
# plt.axis('off')
# plt.imshow(img)
# plt.show()
