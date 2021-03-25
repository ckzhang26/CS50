#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_pop, end_pop; 
    do 
    {
       start_pop = get_int("Enter the starting population:\n"); 
    } 
    while (start_pop < 9);
    
    // TODO: Prompt for end size
    do 
    {
        end_pop = get_int("Enter the ending population:\n");
    } 
    while (end_pop < start_pop);

    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    while (end_pop > start_pop)
    {
        int temp = start_pop;
        start_pop += temp / 3;
        start_pop -= temp / 4;
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", years);
}