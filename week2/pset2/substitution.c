#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

string is_key_valid(string key);
string cipherize(string text, string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    if (strcmp(is_key_valid(argv[1]), "Valid"))
    {
        printf("%s\n", is_key_valid(argv[1]));
        return 1;
    }

    string plaintext = get_string("plaintext:  ");
    string ciphertext = cipherize(plaintext, argv[1]);

    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

string is_key_valid(string key)
{
    char seen[26];
    int seen_index = 0;
    int key_length = strlen(key);

    if (key_length != 26)
    {
        return "Key must contain 26 characters.";
    }

    for (int i = 0; i < key_length; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            return "Key must contain only letters.";
        }
        for (int j = 0; j <= seen_index; j++)
        {
            if (key[i] == seen[j])
            {
                return "Key must contain each letter once.";
            }
        }
        seen[seen_index] = key[i];
        seen_index++;
    }

    return "Valid";
}

string cipherize(string text, string key)
{
    int text_length = strlen(text);

    for (int i = 0; i < text_length; i++)
    {
        if (isalpha(text[i]) != 0)
        {
            bool uppercase = isupper(text[i]) != 0;
            int place = (uppercase ? text[i] - 64 : text[i] - 96) - 1;
            text[i] = uppercase ? toupper(key[place]) : tolower(key[place]);
        }
    }

    return text;
}