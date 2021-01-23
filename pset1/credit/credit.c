#include <stdio.h>
#include <cs50.h>

bool checksum(long n);

int main(void)
{
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 1);

    if (n < 56E14 && n >= 51E14 && checksum(n))
    {
        printf("MASTERCARD\n");
    }
    else if (((n < 5E15 && n >= 4E15) || (n < 5E13 && n >= 4E13)) && checksum(n))
    {
        printf("VISA\n");
    }
    else if (((n < 38E13 && n >= 37E13) || (n < 35E13 && n >= 34E13)) && checksum(n))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

bool checksum(long n)
{
    int sum = 0;
    int doubdig;
    for (long head = n / 10; head > 0; head = head / 100)
    {
        doubdig = 2 * (head % 10);
        sum = sum + doubdig % 10 + doubdig / 10;
    }
    for (long head = n; head > 0; head = head / 100)
    {
        sum = sum + head % 10;
    }
    return sum % 10 == 0;
}