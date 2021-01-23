from cs50 import get_string


text = get_string("Text: ")

l = len([c for c in text if c.isalpha()])
w = 1 + text.count(' ')
s = text.count('.') + text.count('!') + text.count('?')
score = 100 * (0.0588 * l - 0.296 * s) / w - 15.8
grade = int(round(score))

if grade < 1:
    print("Before Grade 1\n")
elif grade >= 16:
    print("Grade 16+\n")
else:
    print(f"Grade {grade}\n")
