#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int d = 4;
    int board[d][d];
    int counter = (d*d) - 1;
    //populate the board by a for loop inside a for loop (for every row do a 4 columns)
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            printf("%i\n",counter);
            board[i][j] = counter;
            counter--;
        }
    }
    //Swap 2 and 1 if the d is even which means the board has odd number of tiles
    if (d % 2 == 0)
    {
        board[d-2][d-2] = 2;
        board[d-3][d-3] = 1;
    }
    return 0;
}