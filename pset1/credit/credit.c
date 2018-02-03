#include <stdio.h>
#include <cs50.h>
#include <math.h>

void check_company(long cc);
bool check_sum(long cc);

//AMEX start with 34 o 37
//MC 51,52,53,54,55
//Visa 4

// Multiply every other digit by 2 starting with second-to-last, then add together
// Add the sum to the sum that werent multiplied by 2
// if the total last digit is total % 10 = 0, number is valid

int main(void)
{
    printf("Number: ");
    long cc = get_long_long();
    if(check_sum(cc))
    {
        check_company(cc);
    }
    else
    {
        printf("INVALID\n");
    }
    return 0;
}

void check_company(long cc)
{
   int first_digit = 0;
   int first_two = 0;
   while (cc > 0){
       cc = cc / 10;
       if (cc <= 99 && cc >= 10){
           first_two = cc;
       }
       if (cc <= 9 && cc > 0){
           first_digit = cc;
       }
   }
   if (first_digit == 4)
   {
       printf("VISA\n");
   }
   else {
       switch(first_two)
       {
            case 51:
            case 52:
            case 53:
            case 54:
            case 55:
                printf("MASTERCARD\n");
                break;
            case 34:
            case 37:
                printf("AMEX\n");
                break;
            default:
                printf("INVALID\n");
       }
   }
}

bool check_sum(long cc){
    int odds = 0;
    int evens = 0;
    int sum = 0;
    int counter = 1;
    while (cc > 0)
    {
        //GET EVEN DIGIT
        if (counter % 2 == 0)
        {
            int digit = cc % 10;
            //MULTIPLY DIGIT BY 2
            digit = digit * 2;
            if (digit >= 10)
            {
                evens += digit / 10;
                evens += digit % 10;
            }
            else
            {
                evens += digit;
            }
        }
        //GET ODD DIGIT
        else
        {
            odds += cc % 10;
        }
        counter++;
        cc = cc / 10;
    }
    sum = odds + evens;
    if (sum % 10 == 0){
        return true;
    }
    else
    {
        return false;
    }
}