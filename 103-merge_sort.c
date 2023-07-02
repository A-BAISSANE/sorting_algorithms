#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

void merge_subarr(int *subarr, int *buff, size_t front, size_t mid, size_t back);
void merge_sort_recursive(int *subarr, int *buff, size_t front, size_t back);
void merge_sort(int *array, size_t size);

void print_array(const int *array, size_t size)
{
    if (array == NULL || size == 0)
        return;

    printf("%d", array[0]);
    for (size_t i = 1; i < size; i++)
        printf(", %d", array[i]);
    printf("\n");
}

void merge_subarr(int *subarr, int *buff, size_t front, size_t mid, size_t back)
{
    size_t i, j, k = 0;

    printf("Merging...\n[left]: ");
    print_array(subarr + front, mid - front);

    printf("[right]: ");
    print_array(subarr + mid, back - mid);

    for (i = front, j = mid; i < mid && j < back; k++)
        buff[k] = (subarr[i] < subarr[j]) ? subarr[i++] : subarr[j++];
    for (; i < mid; i++)
        buff[k++] = subarr[i];
    for (; j < back; j++)
        buff[k++] = subarr[j];
    for (i = front, k = 0; i < back; i++)
        subarr[i] = buff[k++];

    printf("[Done]: ");
    print_array(subarr + front, back - front);
}

void merge_sort_recursive(int *subarr, int *buff, size_t front, size_t back)
{
    size_t mid;

    if (back - front > 1)
    {
        mid = front + (back - front) / 2;
        merge_sort_recursive(subarr, buff, front, mid);
        merge_sort_recursive(subarr, buff, mid, back);
        merge_subarr(subarr, buff, front, mid, back);
    }
}

void merge_sort(int *array, size_t size)
{
    int *buff;

    if (array == NULL || size < 2)
        return;

    buff = malloc(sizeof(int) * size);
    if (buff == NULL)
        return;

    merge_sort_recursive(array, buff, 0, size);

    free(buff);
}

int main(void)
{
    int array[] = {9, 3, 1, 6, 2, 8, 4, 5, 7};
    size_t size = sizeof(array) / sizeof(array[0]);

    printf("Original array: ");
    print_array(array, size);

    merge_sort(array, size);

    printf("Sorted array: ");
    print_array(array, size);

    return 0;
}
