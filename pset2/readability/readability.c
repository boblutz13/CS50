#include <stdio.h>
#include <math.h>
#include <cs50.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");

    int l = count_letters(text);
    int w = count_words(text);
    int s = count_sentences(text);
    float score = 100 * (0.0588 * l - 0.296 * s) / w - 15.8;
    int grade = round(score);

    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        char a = text[i];
        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
        {
            count++;
        }
    }
    return count;
}

int count_words(string text)
{
    int count = 1;
    for (int i = 0; text[i] != '\0'; i++)
    {
        char a = text[i];
        if (a == ' ')
        {
            count++;
        }
    }
    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        char a = text[i];
        if (a == '.' || a == '!' || a == '?')
        {
            count++;
        }
    }
    return count;
}

