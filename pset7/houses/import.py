import cs50
import csv
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python import.py characters.csv")
    exit()

db = cs50.SQL("sqlite:///students.db")

with open(argv[1], "r") as characters:
    reader = csv.DictReader(characters)

    for row in reader:
        names = row["name"].split(' ')

        if len(names) == 2:
            db.execute("INSERT INTO students (first, last, house, birth) VALUES (?, ?, ?, ?)",
                       names[0], names[1], row["house"], row["birth"])

        else:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?)",
                       names[0], names[1], names[2], row["house"], row["birth"])