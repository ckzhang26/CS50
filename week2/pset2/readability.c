#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

string get_input_text(void);
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int calc_grade_level(int letter_count, int word_count, int sentence_count);

int main(void)
{
    string text = get_input_text();
    int letter_count = count_letters(text);
    int word_count = count_words(text);
    int sentence_count = count_sentences(text);
    int grade_level = calc_grade_level(letter_count, word_count, sentence_count);

    if (grade_level > 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade_level);
    }
}

string get_input_text(void)
{
    string text = get_string("Text: ");
    return text;
}

int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] > 64 && text[i] < 91) || (text[i] > 96 && text[i] < 123))
        {
            count++;
        }
    }

    return count;
}

int count_words(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text) + 1; i < n; i++)
    {
        if (text[i] == ' ' || text[i] == '\0')
        {
            count++;
        }
    }

    return count;
}

int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            count++;
        }
    }

    return count;
}

int calc_grade_level(int letter_count, int word_count, int sentence_count)
{
    float l = letter_count / (word_count / 100.0);
    float s = sentence_count / (word_count / 100.0);

    return round(0.0588 * l - 0.296 * s - 15.8);
}