import cs50
import csv
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python roster.py house")
    exit()

db = cs50.SQL("sqlite:///students.db")

house = db.execute("SELECT first, middle, last, birth FROM students WHERE HOUSE = ? ORDER BY last, first", argv[1])

for row in house:
    if not row["middle"]:
        print(f"{row['first']} {row['last']}, born {row['birth']}")
    else:
        print(f"{row['first']} {row['middle']} {row['last']}, born {row['birth']}")