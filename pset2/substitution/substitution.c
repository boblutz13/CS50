#include <stdio.h>
#include <math.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

bool contains_nonletter(string key);
bool contains_duplicate(string key);
char encrypt(string key, char a);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string key = argv[1];

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (contains_duplicate(key))
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    if (contains_nonletter(key))
    {
        printf("Key must only contain alphabetic characters.\n");
        return 1;
    }

    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");

    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        printf("%c", encrypt(key, plaintext[i]));
    }
    printf("\n");
}

bool is_upper(char a)
{
    if (a >= 'A' && a <= 'Z')
    {
        return true;
    }
    return false;
}

bool is_lower(char a)
{
    if (a >= 'a' && a <= 'z')
    {
        return true;
    }
    return false;
}

bool is_letter(char a)
{
    if (is_upper(a) || is_lower(a))
    {
        return true;
    }
    return false;
}

bool contains_nonletter(string key)
{
    for (int i = 0; key[i] != '\0'; i++)
    {
        if (!is_letter(key[i]))
        {
            return true;
        }
    }
    return false;
}

bool contains_duplicate(string key)
{
    for (int i = 0; key[i] != '\0'; i++)
    {
        for (int j = i + 1; key[j] != '\0'; j++)
        {
            if (key[i] == key[j])
            {
                return true;
            }
        }
    }
    return false;
}

char encrypt(string key, char a)
{
    if (is_upper(a))
    {
        return toupper(key[a - 65]);
    }
    if (is_lower(a))
    {
        return tolower(key[a - 97]);
    }
    return a;
}