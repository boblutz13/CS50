#include <stdio.h>
#include <cs50.h>

void print_spaces(int n, int i);
void print_blocks(int n, int i);

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    for (int i = 0; i < n; i++)
    {
        print_spaces(n, i);
        print_blocks(n, i);
        printf("  ");
        print_blocks(n, i);
        printf("\n");
    }
}

void print_spaces(int n, int i)
{
    for (int j = 0; j < n - i - 1; j++)
    {
        printf(" ");
    }
}

void print_blocks(int n, int i)
{
    for (int j = n - i - 1; j < n; j++)
    {
        printf("#");
    }
}