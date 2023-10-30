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
        return "{0} {1}".format(self.x, self.y)

    def __copy__(self):
        return Point(self.x, self.y)


import numpy as np
import matplotlib.pyplot as plt
from PIL import Image


def brezehemAlg(start, end, space, s_color, e_color, control):
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
    dy = abs(end.y - start.y)
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
            control[yp][xp] = 1
        d += dy2
        if d > 0:
            point.y += y_step
            d -= dx2
        point.x += 1


def distance(first, second):
    return np.sqrt((first.x - second.x) ** 2 + (first.y - second.y) ** 2)


def Texture():
    # Создаем изображение размером 64x64 пикселя, заполняя его серым цветом (200, 200, 200)
    imp = np.full((64, 64, 3), 200, dtype='uint8')

    # Определяем набор цветов для текстуры
    colors = [(0, 0, 200), (200, 0, 0), (0, 200, 200), (200, 0, 200), (200, 200, 0), (0, 200, 200), (0, 200, 0),
              (100, 100, 200), (200, 100, 100)]

    # Определяем начальные и конечные точки для размещения цветов на текстуре
    start_points = [(0, 16), (0, 48), (16, 0), (16, 32), (32, 16), (32, 48), (32, 48), (48, 0), (48, 32)]
    end_points = [(16, 32), (16, 64), (32, 16), (32, 48), (48, 32), (48, 64), (48, 64), (64, 16), (64, 48)]

    # Заполняем текстуру цветами в соответствии с заданными параметрами
    for i in range(len(colors)):
        imp[start_points[i][0]:end_points[i][0], start_points[i][1]:end_points[i][1], :] = colors[i]

    return imp


def rastr_polygon(pic, Poly, color=(0, 0, 0), grad=False):
    if not grad:
        colorL = colorR = color
    k = 3
    Poly = np.array(sorted(Poly, key=lambda x: x.x))
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
            xr.x += 1
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
control_matrix = np.full((500, 500), 0)
for i in range(500):
    for j in range(500):
        vp[i, j] = np.random.randint(0, 255, (1, 3))
polygon = [Point(10, 400),
                    Point(350, 400),
                    Point(200, 100),
                    Point(100, 200)
                    ]
polygon.append(Point(10, 400))
# colors = np.array([[255, 0, 0],
#                    [0, 128, 0],
#                    [0, 0, 128],
#                    [255, 0, 255]
#                    ])
# print(colors)
# k = 0
# for p in polygon:
#     vp[p.x, p.y] = colors[k]
#     k += 1
#
# color = np.zeros(3, dtype='int')
# for j in range(0, 3):
#     color[j] = np.random.randint(0, 255)
#
# rastr_polygon(vp, polygon, color)
# plt.imshow(vp)
# plt.show()
# rastr_polygon(vp, polygon, grad=True)

imgtext = True

gorizont = 1
vertical = 1

if (imgtext):
    img = Image.open('crying_cat.jpg')
else:
    img = Image.fromarray(Texture())

p_color = np.array((0, 0, 0))

for i in polygon:
    vp[i.y, i.x] = p_color
    control_matrix[i.y][i.x] = 1

for i in range(len(polygon) - 1):
    brezehemAlg(polygon[i].__copy__(), polygon[i + 1].__copy__(), vp, p_color, p_color, control_matrix)

polygon = np.array(polygon[:4])

my = [polygon[i].y for i in range(len(polygon))]
min_y = min(my)
max_y = max(my)

for i in range(min_y, max_y):
    row = control_matrix[i]
    if 1 in row:
        indices = np.where(row == 1)[0]
        start = indices[0]
        end = indices[-1] + 1
        control_matrix[i][start:end] = 1

height = max_y - min_y
mx = [polygon[i].x for i in range(len(polygon))]
max_x = max(mx)
min_x = min(mx)
width = round((max_x - min_x)/gorizont) + 1
height = round(height/vertical) + 1
img = img.resize((width, height))

imp = np.asarray(img)

for i in range(min_y, max_y):
    count_y = i - min_y
    count_y %= len(imp)
    for j in range(min_x, max_x):
        count_x = j - min_x
        count_x %= len(imp[count_y])
        if control_matrix[i, j] == 1:
            vp[i, j, :] = imp[count_y, count_x, :]

plt.imshow(vp)
plt.show()
