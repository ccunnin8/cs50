#include <stdio.h>
#include <cs50.h>

bool search(int value, int values[],int n);
void sort(int values[], int n);

int main(void)
{

    // int value = atoi(argv[1]);
    int values[] = { 7, 1, 12, 25, 2, 3, 19, 26, 22, 3 };
    int n = 10;
    for (int i = 0; i < n; i++)
    {
        printf("%i",values[i]);
    }
    sort(values,n);
    for (int i = 0; i < 10; i++)
    {
        printf("%i",values[i]);
    }
    return 0;
}
bool search(int value, int values[], int n)
{
   int leftBound = 0;
   int rightBound = n - 1;
   int middle = (leftBound + rightBound) / 2;
   //loop through the array, if left side is lower then the right side then the value is not there
   while (leftBound < rightBound && value != values[middle])
   {
      //break out of the loop if we found the value
       if (value > values[middle])
       {
           leftBound = middle + 1;
       }
       else if (value < values[middle])
       {
           rightBound = middle - 1;
       }
        //find the middle value, take at the end because if we don't then we never get to the right value
        middle = (rightBound + leftBound) / 2;
   }
   return values[middle] == value;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // implement count sort algorithm

    //initialize an array with max value
    int counting_array[65536];

    //go through values, for each number add 1 to the index of counting_array
    for (int i = 0; i < n; i++)
    {
        counting_array[values[i]] += 1;
    }

    //rebuild array in order using the counting array
    int count = 0;
    for (int i = 0; i < 65536; i++)
    {
        if (counting_array[i] != 0)
        {
            for (int j = 0; j < counting_array[i]; j++)
            {
                values[count] = i;
                count++;
            }
        }
        if (count == n)
        {
            break;
        }
    }
}