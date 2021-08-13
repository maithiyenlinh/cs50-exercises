#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get the number card
    long n, number;
    n = get_long("Number: ");
    number = n;
    
    
    //Calculation checksum
    int count = 0;
    int sum = 0;
    int digit, digit1, digit_double;
    do
    {
        digit = n % 10;
        n = n / 10;
        count ++;
        if ((count % 2) == 0)
        {
            //Multiply the other digit by 2
            digit_double = digit * 2;
            if (digit >= 5)
            {
                do
                {
                    digit1 = digit_double % 10;
                    sum = sum + digit1;
                    digit_double = digit_double / 10;
                }
                while (digit_double != 0);
            }
            else
            {
                sum = sum + digit_double;
            }
        }
        else
        {
            sum = sum + digit;
        }
    }
    while (n != 0);
    int result = sum % 10;
    
    //Get information card
    int count1 = 0;
    int m = count - 2;
    do
    {
        number = number / 10;
        count1 ++;
    }
    while (count1 < m);
    
    //Test number card
    if (result == 0)
    {
        // Amex
        if ((count == 15) && ((number == 34) || (number == 37)))
        {
            printf("AMEX\n");
        }
        else if (count == 16)
        {
            //Master card
            if ((number >= 51) && (number <= 55))
            {
                printf("MASTERCARD\n");
            }
            //Visa
            else if ((number >= 40) && (number <= 49))
            {
                printf("VISA\n");
            }
            //Invalid
            else
            {
                printf("INVALID\n");
            }
        }
        //Visa
        else if ((count == 13) && (number >= 40) && (number <= 49))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //Invalid
    else
    {
        printf("INVALID\n");
    }
    
}