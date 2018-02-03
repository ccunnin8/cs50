#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

//This program asks a user for a name
//Changes the name to uppercase initials

int main(void)
{
    //Prompt user for name
    string name = get_string();
    //iterate over name
    for (int i = 0; i < strlen(name)-1; i++){
        //if first char is not space then print uppercase char
        if (i == 0 && name[i] != ' ') {
            printf("%c",toupper(name[0]));
        }
        //skipping whitespace if whitespace follows white space
        else if (name[i] == ' ' && name[i+1] != ' '){
            printf("%c",toupper(name[i+1]));
        }
    }
    printf("\n");
}