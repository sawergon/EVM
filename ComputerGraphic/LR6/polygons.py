# import matplotlib.pyplot as plt
# import matplotlib.patches
# import numpy as np
#
#
class Point(object):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return "{0} {1}".format(self.y, self.x)

    def __copy__(self):
        return Point(self.x, self.y)


#
#
# # Класс треугольного полигона
# class Polygon:
#     def __init__(self, A, B, C):
#         self.A = A
#         self.B = B
#         self.C = C
#
#     def is_inside(self, P):
#         exp1 = (self.A.x - P.x) * (self.B.y - self.A.y) - (self.B.x - self.A.x) * (self.A.y - P.y)
#         exp2 = (self.B.x - P.x) * (self.C.y - self.B.y) - (self.C.x - self.B.x) * (self.B.y - P.y)
#         exp3 = (self.C.x - P.x) * (self.A.y - self.C.y) - (self.A.x - self.C.x) * (self.C.y - P.y)
#         if ((exp1 > 0 and exp2 > 0 and exp3 > 0) or (exp1 < 0 and exp2 < 0 and exp3 < 0)):
#             return True
#         return False
#
# def distance(first, second):
#     return np.sqrt((first.x - second.x) ** 2 + (first.y - second.y) ** 2)
#
#
# def newPosition(oA, oB, oC):
#     Point: A
#     Point: B
#     Point: C
#     if oA.x > oB.x and oA.x > oC.x :
#         A = oA
#         if oB.y < oC.y:
#             B = oB
#             C = oC
#         else:
#             B = oC
#             C = oB
#     elif oB.x > oA.x and oB.x > oC.x:
#         A = oB
#         if oA.y < oC.y:
#             B = oA
#             C = oC
#         else:
#             B = oC
#             C = oA
#     elif oC.x > oA.x and oC.x > oB.x:
#         A = oC
#         if oA.y < oB.y:
#             B = oA
#             C = oB
#         else:
#             B = oB
#             C = oA
#     return A, B, C
#
# def what_color(rA, rB, rC, oA, oB, oC, P):
#     A, B, C = newPosition(oA, oB, oC)
#     # if (C.x == P.x): return np.array([0, 0, 0])
#     #     xm = C.x
#     # kAB = (B.x - A.x) / (B.y - A.y)
#     #     ym = A.y + (xm - A.x) * kAB
#     # else:
#     # if C.y == P.y: return np.array([0, 0, 0])
#     # kCA = (C.x - A.x) / (C.y - A.y)
#     # kPB = (B.x - P.x) / (B.y - P.y)
#     # if (kPB == kCA): return np.array([0, 0, 0])
#     # xm = (B.x - A.x + A.y * kCA - B.y * kPB) / (kCA - kPB)
#     # ym = B.x + (xm - B.y) * kPB
#     # M = Point(xm, ym)
#     # print(M)
#     tAP = distance(A, P)
#     tBP = distance(B, P)
#     tCP = distance(C, P)
#     tAB = distance(A, B)
#     tAC = distance(A, C)
#     tCB = distance(C, B)
#     s = (tBP + tCP + tAP) / 3
#     sA = (tAP + (tAB - tBP) + (tAC - tCP)) / s
#     sB = ((tAB - tAP) + tBP + (tCB - tCP)) / s
#     sC = ((tAC - tAP) + (tCB - tBP) + tCP) / s
#     # colorM = (1 - t) * rA + t * rC
#     # t = distance(M, P) / distance(M, B)
#     # colorP = (1 - t) * colorM + t * rB
#     colorP = sA * rA + sB * rB + sC * rC
#     return colorP
#
# background_color = (np.random.randint(0, 255), np.random.randint(0, 255), np.random.randint(0, 255))
# color = (np.random.randint(0, 255), np.random.randint(0, 255), np.random.randint(0, 255))
# sz = 400
# vp = np.full((sz, sz, 3), background_color, dtype="uint8")
# rA = np.array([0, 0, 255])
# rB = np.array([0, 255, 0])
# rC = np.array([255, 0, 0])
# A = Point(200, 30)
# B = Point(250, 150)
# C = Point(180, 300)
# D = Point(100, 180)
#
# newP = newPosition(A, B, C)
# print("Before:\nA:{0}\nB:{1}\nC:{2}".format(A, B, C))
# print("After:\nA:{0}\nB:{1}\nC:{2}".format(newP[0], newP[1], newP[2]))
#
# pol_list = [Polygon(A, B, C)]
# pol_list.append(Polygon(A, B, D))
# pol = pol_list[1]
# for i in range(sz):
#     for j in range(sz):
#         p = Point(i, j)
#         if (pol.is_inside(p)):
#             vp[i, j] = color
# # print(vp)
# plt.imshow(vp)
# plt.show()
# for i in range(sz):
#     for j in range(sz):
#         p = Point(i, j)
#         if (pol.is_inside(p)):
#             vp[i, j] = what_color(rA, rB, rC, A, B, C, p)
# # print(vp)
#
# plt.imshow(vp)
# plt.show()
#
#
#
#
# # fig, ax = plt.subplots()
# # fv = np.array([(22, 227), (150, 164), (277, 227), (150, 291)])
# # plg = plt.Polygon(fv, color = 'm', fill = False) # fill = True
# # ax.add_patch(plg)
# # fv = [(v[0], v[1] - 150) for v in fv]
# # plg = plt.Polygon(fv, color = 'g')
# # ax.add_patch(plg)
# # ax.set_xlim(0, 300); ax.set_ylim(0, 300)
# # plt.axis('off')
# # plt.show()
# #
# #
# # W = H = 64 # Размер текстуры равен H * W
# # img = np.zeros((H, W, 3), dtype = 'uint8')
# # for i in range(H): # Генерация черно-белой карты текстуры
# #     for j in range(W):
# #         img[i, j, :] = (i & 16 ^ j & 16) * 255
# # plt.axis('off')
# # plt.imshow(img)
# # plt.show()
# #
# # img = np.full((H, W, 3), 200, dtype = 'uint8')
# # img[:16, 16:32, :2] = 0   # (0, 0, 200)
# # img[:16, 48:, 2:] = 0     # (200, 0, 0)
# # img[16:32, :16, 0] = 0    # (0, 200, 200)
# # img[16:32, 32:48, 1] = 0  # (200, 0, 200)
# # img[32:48, 16:32, 2] = 0  # (200, 200, 0)
# # img[32:48, 48:, 0] = 0    # (0, 200, 200)
# # img[32:48, 48:, 2] = 0    # (0, 200, 0)
# # img[48:, :16, :2] = 100   # (100, 100, 200)
# # img[48:, 32:48, 2:] = 100 # (200, 100, 100)
# # plt.axis('off')
# # plt.imshow(img)
# # plt.show()

import numpy as np
import matplotlib.pyplot as plt


def brezehemAlg(start, end, space, s_color, e_color):
    vp_width, vp_height, _ = space.shape
    start.y = int(start.y)
    end.y = int(end.y)
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
    dist = distance(start, end)
    while point.x < end.x:
        if 0 <= point.x < vp_width and 0 <= point.y < vp_height:
            if steep:
                xp, yp = point.y, point.x
            else:
                xp, yp = point.x, point.y
            dst = distance(start, point)
            if dist:
                color = s_color + (e_color - s_color) * dst / dist
            else:
                color = s_color
            space[yp][xp] = color
        d += dy2
        if d > 0:
            point.y += y_step
            d -= dx2
        point.x += 1


def distance(first, second):
    return np.sqrt((first.x - second.x) ** 2 + (first.y - second.y) ** 2)


def rastr_polygon(pic, Poly, color=(0, 0, 0), grad=False):
    if not grad:
        colorL = colorR = color
    k = 3
    Poly = np.array(sorted(Poly, key=lambda x:x.x))
    x = Poly[0].x
    xMax = Poly[len(Poly) - 1].x
    Pl = Poly[1]
    Pr = Poly[2]
    if (Pl.y > Pr.y):
        Pr, Pl = Pl, Pr
    xE = min(Pl.x, Pr.x)
    xl = Point(x, Poly[0].y)
    xr = Point(x, Poly[0].y)
    dyl = (xl.y - Pl.y) / (xl.x - Pl.x)
    dyr = (xr.y - Pr.y) / (xr.x - Pr.x)
    prevL = Poly[0]
    prevR = Poly[0]

    distL = distance(prevL, Pl)
    distR = distance(prevR, Pr)
    while xr.x < xMax:
        while xr.x < xE:
            xl.x += 1
            xr.x +=1
            xl.y += dyl
            xr.y += dyr
            if (grad):
                colorBeg = np.array(pic[prevL.x, prevL.y], dtype='int')
                colorEnd = np.array(pic[Pl.x, Pl.y], dtype='int')
                colorL = colorBeg + (colorEnd - colorBeg) * (distance(prevL, xl) / distL)

                colorBeg = np.array(pic[prevR.x, prevR.y], dtype='int')
                colorEnd = np.array(pic[Pr.x, Pr.y], dtype='int')
                colorR = colorBeg + (colorEnd - colorBeg) * (distance(prevR, xr) / distR)

                colorL = np.array(colorL, dtype='int')
                colorR = np.array(colorR, dtype='int')
            brezehemAlg(xl.__copy__(), xr.__copy__(), pic, colorL, colorR)
        if xl.x == xMax:
            break
        Pe = Poly[k]
        if (k < len(Poly) - 1):
            k += 1

        if (xl.x == Pl.x):
            temp = Pl
            Pl = Pe
            flag = True
        else:
            temp = Pr
            Pr = Pe
            flag = False

        if (Pl.y > Pr.y):
            Pr, Pl = Pl, Pr
            flag = not flag

        if flag:
            dyl = (xl.y - Pl.y) / (xl.x - Pl.x)
            prevL = temp
            distL = distance(prevL, Pl)
        else:
            dyr = (xr.y - Pr.y) / (xr.x - Pr.x)
            prevR = temp
            distR = distance(prevR, Pr)

        xE = min(Pl.x, Pr.x)


vp = np.full((500, 500, 3), (0, 0, 0), dtype='uint8')
for i in range(500):
    for j in range(500):
        vp[i, j] = np.random.randint(0, 255, (1, 3))
polygon = np.array([Point(10, 400),
                    Point(250, 400),
                    Point(100, 10),
                    Point(380, 60)
                    ])
colors = np.array([[255, 0, 0],
                  [0, 128, 0],
                  [0, 0, 128],
                  [255, 0, 255]
                  ])
print(colors)
k = 0
for p in polygon:
    vp[p.x, p.y] = colors[k]
    k += 1

color = np.zeros(3, dtype='int')
for j in range(0, 3):
    color[j] = np.random.randint(0, 255)

rastr_polygon(vp, polygon, color)
plt.imshow(vp)
plt.show()
rastr_polygon(vp, polygon, grad=True)

plt.imshow(vp)
plt.show()
