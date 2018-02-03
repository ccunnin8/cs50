#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

// CS50.h methods
// get_char, get_double, get_float, get_int, get_long_long
// Data Types
// bool, char, double, float, int, long long
// Integer overflow  (finite amount of memory, can only count so high)
// Floating point imprecision
// 1/3 in human world = .33333333~



// int main(void)
// {
//     string s = get_string();
//     if (s != NULL)
//     int length = strlen(s)
//     {
//           for (int i = 0; i < length; i++)
//             {
//                 printf("%c+",s[i]);
//             }
//     }
// }

int main(int argc, string argv[])
{
   if (argc == 2)
   {
       printf("hello, %s\n",argv[1]);
   }
   else {
       printf("hello, world");
   }
}