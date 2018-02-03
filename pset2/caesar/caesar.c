#include <stdio.h>
#include <cs50.h>
#include <string.h>

void cipher(string s, int key);

//THis is a program that takes a command line argument, a key
//Asks a user for a string input
//Encrypts the output

int main(int argc, string argv[])
{
    //Handle Errors if user does not input key
    if (argc != 2){
        printf("Please enter a key\n");
        return 1;
    }
    else
    {
        //Get input from user for string to encrypt
        printf("plaintext: ");
        string s = get_string();
        //print encrypted text
        printf("ciphertext: ");
        cipher(s, atoi(argv[1]));
        printf("\n");
    }
    return 0;
}

//prints each new char after being encrypted
void cipher(string s, int key)
{
    for (int i = 0; i < strlen(s); i++)
    {
        int new_char = 0;
        int val = (int)s[i];
        key = key % 26;
        //Handles uppercase

        if (val >= 65 && val <= 90)
        {
            //wraps around
            if (key + val > 90)
            {
                new_char = 64 + ((key + val) - 90);
            }
            else
            {
                new_char = key + val;
            }
        }
        //Handles lowercase
        else
        {
            //wraps around
            if (key + val > 122)
            {
                new_char = 96 + ((key + val) - 122);
            }
            else
            {
                new_char = key + val;
            }
        }
        printf("%c",(char)new_char);
    }
}