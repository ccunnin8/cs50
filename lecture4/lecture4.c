#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(void)
{
    printf("s: ");
    string s = get_string();
    string t;
    printf("%s", s == t ? "same" : "different");
    return 0;
}