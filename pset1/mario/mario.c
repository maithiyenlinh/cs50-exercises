#include <cs50.h>
#include <stdio.h>

void space(void)
{
    printf(" ");
}

void hash(void)
{
    printf("#");
}

int main(void)
{
    //Prompt for hight of the pyramids
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while ((n < 1) || (n > 8));
    
    //Building the pyramids
    for (int i = 1; i <= n; i++)
    {
        //Print space
        for (int j = 1; j <= n - i; j++)
        {
            space();
        }
        
        //Print hash
        for (int j = 1; j <= i; j++)
        {
            hash();
        }
        
        //Print space
        for (int j = 0; j < 2; j++)
        {
            space();
        }
        
        //Print hash
        for (int j = 1; j <= i; j++)
        {
            hash();
        }
        
        //Finish row
        printf("\n");
        
    }
}