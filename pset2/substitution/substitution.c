#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

//Make the standard alphabetic
int *get_alphabet(void)
{
    static int let[52];
    int i = 0;
    char c;
    // Upper letter
    for (c = 'A'; c <= 'Z'; c++)
    {
        let[i] = c;
        i ++;
    }
    //Lower letter
    for (c = 'a'; c <= 'z'; c++)
    {
        let[i] = c;
        i ++;
    }
    return let;
}

//Some functions in program
int *new_alphebetic(string key, int len);
void transfer_character(string key, int len, string word, int len2);
int check_dup(string key, int len);
int check_non_alphabetic(string key, int len);


int main(int argc, string argv[])
{
    //no key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // key with invalid length
    int len = strlen(argv[1]);
    if (len != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    
    //key with dup or non-character
    int dup = check_dup(argv[1], len);
    int non = check_non_alphabetic(argv[1], len);
    if ((dup != 0) || (non != 0))
    {
        printf("Duplicate characters or invalid characters in key\n");
        return 1;
    }
    
    //get the word need changing
    string word = get_string("plaintext: ");
    int len2 = strlen(word);
    
    //print the word after changing follow key
    transfer_character(argv[1], len, word, len2);

    return 0;
}

//checking the duplication character in key
int check_dup(string key, int len)
{
    int dup = 0;
    int c, d, e, g;
    int *let;
    let = get_alphabet();
    for (int i = 0; i < (len - 1); i++)
    {
        c = key[i];
        for (int k = 0; k < 52; k++)
        {
            d = let[k];
            if (c == d)
            {
                if isupper(c)
                {
                    e = let[k + 26];
                }
                else if islower(c)
                {
                    e = let[k - 26];
                }
            }
        }
        for (int j = (i + 1); j < len; j++)
        {
            g = key[j];
            if ((c == g) || (e == g))
            {
                dup = dup + 1;
            }
        }
    }
    return dup;
}

//check the non alphabetic in key
int check_non_alphabetic(string key, int len)
{
    int *let;
    let = get_alphabet();
    int c, d, non;
    int count = 0;
    //check every character in key appears in the alphebetic or no 
    for (int i = 0; i < len; i++)
    {
        c = key[i];
        for (int j = 0; j < 52; j++)
        {
            d = let[j];
            if (c == d)
            {
                count = count + 1;
                break;
            }
        }
    }
    // if all appear 
    if (count == 26)
    {
        // key without non-character
        non = 0;
    }
    else
    {
        // key with non-character
        non = 1;
    }
    return non;
}

//make the new alphabetic following the key
int *new_alphebetic(string key, int len)
{
    int c, d;
    int *old_let;
    old_let = get_alphabet();
    static int new_let[52];
    for (int i = 0; i < len; i++)
    {
        c = key[i];
        //Upper character
        if isupper(c)
        {
            new_let[i] = c;
            for (int j = 0; j < 52; j++)
            {
                d = old_let[j];
                if (c == d)
                {
                    new_let[(i + 26)] = old_let[(j + 26)];
                    break;
                }
            }
        }
        //lower character
        else if islower(c)
        {
            new_let[(i + 26)] = c;
            for (int j = 0; j < 52; j++)
            {
                d = old_let[j];
                if (c == d)
                {
                    new_let[i] = old_let[(j - 26)];
                    break;
                }
            }
        }
    }
    return new_let;
}

//changing the word following the key
void transfer_character(string key, int len, string word, int len2)
{
    int *old_let;
    old_let = get_alphabet();
    int *new_let;
    new_let = new_alphebetic(key, len);
    int new_word[(len2)];
    int c, d, non;
    //make the array same word inputs
    //check the character in word with standard alphabetic
    for (int i = 0; i < len2; i++)
    {
        c = word[i];
        //replace the character by new alphabetic follow key
        for (int j = 0; j < 52; j++)
        {
            d = old_let[j];
            if (c == d)
            {
                new_word[i] = new_let[j];
                non = 0;
                break;
            }
            else
            {
                non = 1;
            }
        }
        if (non == 1)
        {
            new_word[i] = word[i];
        }
    }
    //print the word after changing
    printf("ciphertext: ");
    for (int k = 0; k < len2; k++)
    {
        printf("%c", new_word[k]);
    }
    printf("\n");
}