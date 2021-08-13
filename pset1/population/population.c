#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int s;
    do
    {
        s = get_int("Start size: ");
    }
    while (s < 9);

    // TODO: Prompt for end size
    int e;
    do
    {
        e = get_int("End size: ");
    }
    while (e < s);

    // TODO: Calculate number of years until we reach threshold
    int n = 0;
    int e1 = s;
    while (e1 < e)
    {
        e1 = e1 + e1 / 3 - e1 / 4;
        n ++;
    }
    
    // TODO: Print number of years
    printf("Years: %i\n", n);
}