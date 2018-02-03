#include <stdio.h>
#include <cs50.h>

int bottle_water( int min);

int main(void)
{
    printf("How long are your showers? (answer in minutes)\nTime: ");
    int minutes = get_int();
    printf("Minutes : %i\n",minutes);
    printf("Bottles: %i\n",bottle_water(minutes));

}


int bottle_water(int min)
{
    int ounces = 192 * min;
    return ounces / 16;
}