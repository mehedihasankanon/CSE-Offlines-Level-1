#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *array;
    int max_size;
    int size;
    int pos;
} arrayList;

void init(arrayList *list)
{
    list->max_size = 2;
    list->size = 0;
    list->array = (int *)malloc(list->max_size * sizeof(int));
    list->pos = 0;
}

void free_list(arrayList *list)
{
    free(list->array);
    list->max_size = 0;
    list->size = 0;
    list->pos = 0;
}

void increase_capacity(arrayList *list)
{
    printf("Capacity increased from %d to %d\n", list->max_size, list->max_size * 2);
    int *new_arr = (int *)malloc(list->max_size * 2 * sizeof(int));
    for (int i = 0; i < list->size; i++)
        new_arr[i] = list->array[i];
    list->max_size *= 2;
    free(list->array);
    list->array = new_arr;
}

void decrease_capacity(arrayList *list)
{

    if (list->max_size == 2)
        return;

    printf("Capacity decreased from %d to %d\n", list->max_size, list->max_size / 2);
    int *new_arr = (int *)malloc((list->max_size / 2) * sizeof(int));
    for (int i = 0; i < list->size; i++)
        new_arr[i] = list->array[i];
    list->max_size /= 2;
    free(list->array);
    list->array = new_arr;
}

void print(arrayList *list)
{

    if (list->size == 0)
    {
        printf("[ . ]\n");
        return;
    }

    printf("[");
    for (int i = 0; i < list->pos; i++)
    {
        printf(" %d", list->array[i]);
    }
    if (list->pos)
    {
        printf("|");
    }
    for (int i = list->pos; i < list->size; i++)
    {
        printf(" %d", list->array[i]);
    }
    printf(" ]\n");
}

void insert(int item, arrayList *list)
{
    if ((list->size) * 2 == list->max_size)
    {
        increase_capacity(list);
    }
    list->size++;

    for (int i = list->size; i > list->pos; i--)
        list->array[i] = list->array[i - 1];

    list->array[list->pos] = item;

    list->pos++;

    print(list);
}

int size(arrayList *list);

int delete_cur(arrayList *list)
{
    if (!size(list))
    {
        print(list);
        return -1;
    }
    list->pos--;
    int temp = list->array[list->pos];
    for (int i = list->pos; i < list->size - 1; i++)
    {
        list->array[i] = list->array[i + 1];
    }
    list->size--;

    if (list->size * 4 < list->max_size)
    {
        decrease_capacity(list);
    }
    list->pos++;

    list->pos = list->pos < list->size ? list->pos : list->size;

    print(list);
    return temp;
}

void append(int item, arrayList *list)
{
    if ((list->size) * 2 == list->max_size)
    {
        increase_capacity(list);
    }

    list->array[list->size] = item;
    list->size++;

    if (!list->pos)
        list->pos++;

    print(list);
}

int size(arrayList *list)
{
    return list->size;
}

void prev(int n, arrayList *list)
{
    while (n > 0 && list->pos > 1)
    {
        n--;
        list->pos--;
    }
    print(list);
}

void next(int n, arrayList *list)
{
    while (n > 0 && list->pos < list->size)
    {
        n--;
        list->pos++;
    }
    print(list);
}

int is_present(int n, arrayList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        if (list->array[i] == n)
            return 1;
    }
    return 0;
}

void clear(arrayList *list)
{
    list->size = 0;
    list->pos = 0;
    print(list);
}

void delete_item(int item, arrayList *list)
{
    for (int i = 0; i < list->size; i++)
    {
        if (list->array[i] == item)
        {
            for (int j = i + 1; j < list->size; j++)
            {
                list->array[j - 1] = list->array[j];
            }
            list->size--;
            if (list->size * 4 < list->max_size)
            {
                decrease_capacity(list);
            }
            if (list->pos > i + 1)
                list->pos--;
            list->pos = list->pos < list->size ? list->pos : list->size;
            print(list);
            return;
        }
    }
    printf("%d not found\n", item);
}

void swap_ind(int ind1, int ind2, arrayList *list)
{

    if (ind1 == ind2)
    {
        print(list);
        return;
    }

    int sz = size(list);
    if (ind1 >= sz || ind2 >= sz)
    {
        printf("Swap: Out of bounds access\n");
        return;
    }

    int temp = list->array[ind1];
    list->array[ind1] = list->array[ind2];
    list->array[ind2] = temp;

    print(list);
}