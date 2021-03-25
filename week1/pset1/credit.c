#include <stdio.h>
#include <cs50.h>
#include <stdbool.h>

long get_input(void);
bool is_checksum_valid(long);
string determine_card(long);
int digit_count = 0;

int main(void)
{
    long number = get_input();
    bool checksum_valid = is_checksum_valid(number);
    string card_type = determine_card(number);

    if (checksum_valid)
    {
        printf("%s\n", card_type);
    }
    else
    {
        printf("INVALID\n");
    }
}

long get_input(void)
{
    long number;
    do
    {
        number = get_long("Number:\n");
    }
    while (!number);

    return number;
}

bool is_checksum_valid(long number)
{
    int mult_sum = 0, unmult_sum = 0;
    while (number >= 1)
    {
        // multiplied digits
        if (digit_count % 2 == 1)
        {
            int product = (number % 10) * 2;
            // add product digits
            while (product >= 1)
            {
                mult_sum += product % 10;
                product /= 10;
            }
        }
        // not multiplied digits
        else
        {
            unmult_sum += number % 10;
        }

        number /= 10;
        digit_count++;
    }

    return (mult_sum + unmult_sum) % 10 == 0 ? true : false;
}

string determine_card(long number)
{
    string card_type;

    switch (digit_count)
    {
        case 13:
            while (number > 10)
            {
                number /= 10;
            }
            if (number == 4) 
            {
                card_type =  "VISA";
            }
            else
            {
                return "INVALID";
            }
            break;
        case 15:
            while (number >= 100)
            {
                number /= 10;
            }
            if (number == 34 || number == 37) 
            {
                card_type = "AMEX";
            }
            else 
            {
                card_type = "INVALID";
            }
            break;
        case 16:
            while (number >= 100)
            {
                number /= 10;
            }
            if (number > 50 && number < 56) 
            {
                card_type = "MASTERCARD";
            }
            else if (number / 10 == 4) 
            {
                card_type = "VISA";
            }
            else 
            {
                card_type = "INVALID";
            }
            break;
        default:
            card_type = "INVALID";
    }

    return card_type;
}