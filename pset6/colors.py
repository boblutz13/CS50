import random

file = open("colors.txt", "w")

colors_per_square = 4
num_squares = 100
colors = ["Bright teal", "Orange", "Brown",
          "Light pink", "Purple", "Grey",
          "Hot pink", "Light green", "Maroon",
          "Yellow", "Dark Teal", "Light blue",
          "Dark Green", "Kelly green", "Black",
          "White", "Medium pink", "Gold",
          "Coral", "Tan", "Red", "Dark blue"]

for i in range(num_squares):
    indices = random.sample(range(len(colors)), colors_per_square)
    file.write(f"Square {i + 1}:\r\n")
    for j in range(colors_per_square):
        file.write(f"Color {j + 1}: {colors[indices[j]]}\r\n")

    if i < num_squares - 1:
        file.write("\r\n")

file.close()