#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool is_key_valid(string key);
string cipherize(int key, string text);

int main(int argc, string argv[])
{
    // check for correct number of command line arguments (1)
    // check that command line argument is a non-negative integer
    // if invalid command line argument print error message and return 1
    if (argc != 2 || !is_key_valid(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // get plaintext string from user
    // initialize cipher string
    // loop over each letter in plaintext
    // shift letter by key
    // add letter to cipher
    // print cipher and return 0
    string plaintext = get_string("Plaintext:  ");
    string ciphertext = cipherize(strtol(argv[1], NULL, 10), plaintext);
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

bool is_key_valid(string key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (key[i] < 48 || key[i] > 57)
        {
            return false;
        }
    }

    return true;
}

string cipherize(int key, string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] > 64 && text[i] < 91)
        {
            text[i] = (((text[i] - 64) + key) % 26) + 64;
        }
        else if (text[i] > 96 && text[i] < 123)
        {
            text[i] = (((text[i] - 96) + key) % 26) + 96;
        }
        else
        {
            text[i] = text[i];
        }
    }

    return text;
}