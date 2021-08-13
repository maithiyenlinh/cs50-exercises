#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int character_score(int c, int let[])
{
    int point_c;
    for (int i = 0; i < 26; i++)
    {
        if (c == let[i])
        {
            point_c = POINTS[i];
            break;
        }
        else
        {
            point_c = 0;
        }
    }
    return point_c;
}

int compute_score(string word)
{
    // TODO: Compute and return score for string
    
    int let1[26];
    int let2[26];
    
    //Letters of the alphabet (upper)
    int k = 0;
    for (char c = 'A'; c <= 'Z'; c++)
    {
        let1[k] = c;
        k ++;
    }
    
    //Letters of the alphabet (lower)
    k = 0;
    for (char c = 'a'; c <= 'z'; c++)
    {
        let2[k] = c;
        k ++;
    }
    
    // Length of the string
    int len = strlen(word);
    
    //check the character in string
    int c;
    int sum = 0;
    int point_c;
    for (int i = 0; i < len; i++)
    {
        c = word[i];
        if isupper(c)
        {
            point_c = character_score(c, let1);
        }
        else if islower(c)
        {
            point_c = character_score(c, let2);
        }
        else
        {
            point_c = 0;
        }
        sum = sum + point_c;
    }
    return sum;
}

