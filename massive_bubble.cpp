#include <TXLib.h>
#include <stdio.h>



int bubble_sort(int quantity, int* num_data);

//-----------------------------------------------------------------------------

int main()
{
    int num_data[] = {5, 3, 7, 13, 200, 56, 2, 42, 96, 3245, 54, 6, 1, 46, 0};
    int quantity = sizeof(num_data) / sizeof(num_data[0]);

    int swaps = bubble_sort(quantity, num_data);

    printf("Отсортированный массив:  \n");

    for (int k = 0; k < quantity; k++)
    {
        printf(" %d ", num_data[k]);
    }

    printf("\nКоличество итераций:   %d \n", swaps);

}

//-----------------------------------------------------------------------------


int bubble_sort(int quantity, int* num_data)
{
    int counter = 0;

    for (int i = 0; i < quantity - 1; i++)
    {
        for (int j = 0; j < quantity - i - 1; j++)
        {
            if (num_data[j] > num_data[j + 1])
            {
                int min_num = num_data[j];
                num_data[j] = num_data[j + 1];
                num_data[j + 1] = min_num;
                counter++;
            }
        }
    }
    return counter;
}







