#include <stdio.h>
#include <cs50.h>

void generate(int height);
void aligner(int blankspaces);
void blocks(int row);

int main(void)
{
    //prompt user for half pyramid height
    //make sure it's none negative and less then 23
    int height;
    do
    {
        printf("Height: ");
        height = get_int();
    }
    while (height < 0 || height > 23);
    generate(height);
}

void generate(int height)
{
    int width = height;
    //for each row (height)
    for (int row = 1; row <= height; row++)
    {
        //print width spaces - (# * row)
        int blankspaces = width - row;
        aligner(blankspaces);
        //print # * row
        blocks(row);
        //print 2 spaces
        printf("  ");
        //print # * row
        blocks(row);
        printf("\n");
    }
}

void aligner(int blankspaces)
{
    for (int i = 0; i < blankspaces; i++)
    {
        printf(" ");
    }
}

void blocks(int row)
{
    for (int i = 0; i < row; i++)
    {
        printf("#");
    }
}