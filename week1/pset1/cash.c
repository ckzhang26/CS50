#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void) 
{
    // prompt user for input
    float change;
    do 
    {
        change = get_float("Change owed:\n");
    }
    while (change < 0);
    
    //convert change to cents
    int cents = round(change * 100);
    
    // counter for number of coins
    int coins = 0;
    
    while (cents > 0) 
    {
        // check if quarters can be given
        if (cents >= 25) 
        {
            cents -= 25;
        }
        // check if dimes can be given
        else if (cents >= 10)
        {
            cents -= 10;
        }
        // check if nickels can be given
        else if (cents >= 5) 
        {
            cents -= 5;
        }
        // only coin left is penny
        else 
        {
            cents -= 1;
        }
        // increment coins
        coins++;
    }
    
    printf("%i\n", coins);
}