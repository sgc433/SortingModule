#include <stdio.h>
#include "sort.h"


int main()
{
    char char_arr[] = {'a', 'c', 'e', 'b', 'd'};
    int char_size = sizeof(char_arr) / sizeof(char);

    printf("Original char array: ");
    for (int i = 0; i < char_size; i++)
    {
        printf("%c ", char_arr[i]);
    }
    printf("\n");

    int result = sort(char_arr, char_size, sizeof(char), compare_char, SORT_HEAP, DIR_ASCENDING);

    if (result == ERR_SUCCESS)
    {
        printf("Sorted char array:");
        for (int i = 0; i < char_size; i++)
        {
            printf("%c ", char_arr[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Error: %d\n", result);
    }

    int int_arr[] = {64, 34, 25, 12, 22, 11, 90};
    int int_size = sizeof(int_arr) / sizeof(int);

    printf("\nOriginal int array: ");
    for (int i = 0; i < int_size; i++)
    {
        printf("%d ", int_arr[i]);
    }
    printf("\n");

    result = sort(int_arr, int_size, sizeof(int), compare_int, SORT_QUICK, DIR_DESCENDING);

    if (result == ERR_SUCCESS)
    {
        printf("Sorted int array: ");
        for (int i = 0; i < int_size; i++)
        {
            printf("%d ", int_arr[i]);
        }
        printf("\n");
    }
    else
    {
        printf("Error: %d\n", result);
    }

    return 0;
}