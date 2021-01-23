from cs50 import get_int


def draw(h, i):
    if i <= h:
        print(" " * (h - i) + "#" * i + "  " + "#" * i)
        draw(h, i + 1)


while True:
    h = get_int("Height: ")
    if 0 < h < 9:
        break

draw(h, 1)