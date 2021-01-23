import csv
from sys import argv, exit


def count_reps(STR, seq):
    reps = [0]
    current_rep = 1
    STR_len = len(STR)
    i1 = seq.find(STR)

    while i1 != -1:
        i2 = seq.find(STR, i1 + 1)
        if i2 - i1 == STR_len:
            current_rep += 1
        else:
            reps.append(current_rep)
            current_rep = 1
        i1 = i2

    return max(reps)


if len(argv) != 3:
    print("Usage: python dna.py database sequence")
    exit()

with open(argv[1]) as db_file, open(argv[2], "r") as seq_file:
    db = list(csv.reader(db_file))
    seq = seq_file.read()

    profile = []

    for STR in db[0][1:]:
        profile.append(str(count_reps(STR, seq)))

    for row in db[1:]:
        if profile == row[1:]:
            print(row[0])
            exit()

    print("No match")