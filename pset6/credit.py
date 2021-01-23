from cs50 import get_int


def checksum(n):
    sum = 0
    while n != 0:
        d = 2*((n // 10) % 10)
        sum += (n % 10) + (d % 10) + (d // 10)
        n //= 100
    return sum % 10 == 0


while True:
    n = get_int("Number: ")
    if (n > 0):
        break

if n < 56E14 and n >= 51E14 and checksum(n):
    print("MASTERCARD\n")
elif ((n < 5E15 and n >= 4E15) or (n < 5E13 and n >= 4E13)) and checksum(n):
    print("VISA\n")
elif ((n < 38E13 and n >= 37E13) or (n < 35E13 and n >= 34E13)) and checksum(n):
    print("AMEX\n")
else:
    print("INVALID\n")