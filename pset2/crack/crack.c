#define _XOPEN_SOURCE

#include <stdio.h>
#include <cs50.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int brute_force(string salt, string hash);
bool check_hash(char guess[], string salt, string hash);

int main(int argc, string argv[])
{
    if (argc != 2)
    //Return 1 if the user did not enter a hashed password
    {
        printf("You need to enter a hashed password as an argument on the command line\n");
        return 1;
    }
    //store the input of the user in a string
    string hash = argv[1];

    //figure out what the salt is
    char salt[3];
    salt[0] = argv[1][0];
    salt[1] = argv[1][1];

    //create a character array of up to 4 spaces
    brute_force(salt,hash);
    return 0;
}

int brute_force(string salt, string hash)
{
    //all the characters in the alphabet, upper and lowercase  len = 52
    char alpha1[57] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefijklmnoqrstuwyz\0";
    //initial guess1, guess2, guess3, guess4, which are 1, 2, 3, and 4 character strings (permutations of alpha1)
    char guess1[5] = "";
    guess1[4] = '\0';
    char guess2[4] = "";
    guess2[3] = '\0';
    char guess3[3] = "";
    guess3[2] = '\0';
    char guess4[2] = " \0";
    guess4[1] = '\0';
    //four for loops to generate every combo of A-Za-z A-Za-z A-Za-z A-Za-z
    for (int a = 0; a < strlen(alpha1); a++)
    {
        guess4[0] = alpha1[a];
        if(check_hash(guess4,salt,hash))
        {
            return 0;
        }
        for (int b = 0; b < strlen(alpha1); b++)
        {
            guess3[0] = alpha1[a];
            guess3[1] = alpha1[b];
            if (check_hash(guess3,salt,hash))
            {
                return 0;
            }
            for (int c = 0; c < strlen(alpha1); c ++)
            {
                guess2[0] = alpha1[a];
                guess2[1] = alpha1[b];
                guess2[2] = alpha1[c];
                if(check_hash(guess2,salt,hash))
                {
                    return 0;
                }
                for (int d = 0; d < strlen(alpha1); d++)
                {
                    guess1[0] = alpha1[a];
                    guess1[1] = alpha1[b];
                    guess1[2] = alpha1[c];
                    guess1[3] = alpha1[d];
                    if(check_hash(guess1,salt,hash))
                    {
                        return 0;
                    }
                }
            }
        }
    }
    //return fail is the program fails to find a hashed guess that equals the hash passed in, return -1
    printf("Fail");
    return -1;
}

//return true if hashed guess = hash passed in
bool check_hash(char guess[], string salt, string hash)
{
    if (strcmp(hash,crypt(guess,salt)) == 0)
    {
        printf("%s",guess);
        return true;
    }
    return false;
}