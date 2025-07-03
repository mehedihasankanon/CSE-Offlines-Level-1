#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int element;
    struct node *next;
    struct node *prev;
} node;

typedef struct
{
    // declare head, tail, cur and other variables you need
    node *head;
    node *tail;
    node *cur;
} linkedList;

void clear(linkedList *list);

void init(linkedList *list)
{
    // implement initialization
    list->head = NULL;
    list->cur = list->head;
    list->tail = list->head;
}

void free_list(linkedList *list)
{
    // implement destruction of list
    node *ls = list->head;
    while (ls != NULL)
    {
        node *ls1 = ls->next;
        free(ls);
        ls = ls1;
    }
    list->head = list->cur = list->tail = NULL;
}

void print(linkedList *list)
{
    if (list->head == NULL)
    {
        printf("\n");
        return;
    }

    node *ls = list->head;
    // printf("[");
    while (ls != NULL)
    {
        printf(" %d", ls->element);
        // if (ls == list->cur)
        //     printf("|");
        ls = ls->next;
    }
    printf(" \n");
}

void insert(int item, linkedList *list)
{
    if (!list->head)
    {
        node *el = (node *)malloc(sizeof(node));
        el->element = item;
        el->next = NULL;
        el->prev = NULL;
        list->head = el;
        list->tail = el;
        list->cur = el;

        // print(list);

        return;
    }

    node *el = (node *)malloc(sizeof(node));
    el->element = item;
    el->next = list->cur->next;
    el->prev = list->cur;
    list->cur->next = el;
    if (el->next)
        el->next->prev = el;
    list->cur = el;
    if (list->cur->next == NULL)
        list->tail = list->cur;

    // print(list);
}

int delete_cur(linkedList *list)
{
    // implement deletion of current index function

    if (!list->cur)
    {
        // print(list);
        return 0;
    }

    int x = list->cur->element;

    if (list->cur == list->head)
    {
        if (list->head == list->tail)
        {
            clear(list);
            return x;
        }

        node *del = list->cur;
        if (list->cur->next)
            list->cur->next->prev = NULL;
        list->head = list->cur->next;
        list->cur = list->cur->next;
        free(del);
        // print(list);
        return x;
    }

    if (list->cur == list->tail)
    {
        node *del = list->cur;
        if (list->cur->prev)
            list->cur->prev->next = NULL;
        list->tail = list->cur->prev;
        list->cur = list->cur->prev;
        free(del);
        // print(list);
        return x;
    }

    node *del = list->cur;
    if (list->cur->prev)
        list->cur->prev->next = list->cur->next;
    if (list->cur->next)
        list->cur->next->prev = list->cur->prev;
    if (list->cur->next)
        list->cur = list->cur->next;
    else if (list->cur->prev)
        list->cur = list->cur->prev;

    free(del);
    // print(list);
    return x;
}

void append(int item, linkedList *list)
{
    // implement append function

    if (!list->tail)
    {
        node *el = (node *)malloc(sizeof(node));
        el->element = item;
        el->next = NULL;
        el->prev = NULL;
        list->head = el;
        list->tail = el;
        list->cur = el;
        // print(list);
        return;
    }

    node *el = (node *)malloc(sizeof(node));
    list->tail->next = el;
    el->element = item;
    el->next = NULL;
    el->prev = list->tail;
    list->tail = el;
    // print(list);
}

int size(linkedList *list)
{
    // implement size function
    if (list == NULL)
        return 0;
    node *ls = list->head;
    int size = 0;
    while (ls)
    {
        ls = ls->next;
        size++;
    }
    return size;
}

int is_present(int n, linkedList *list)
{
    // implement presence checking function
    node *ls = list->head;
    while (ls && ls->element != n)
        ls = ls->next;

    if (ls && ls->element == n)
        return 1;

    return 0;
}

void clear(linkedList *list)
{
    // implement list clearing function
    node *ls = list->head;
    while (ls)
    {
        node *curr = ls;
        ls = ls->next;
        free(curr);
    }
    list->head = NULL;
    list->tail = NULL;
    list->cur = NULL;
    // print(list);
}

void delete_item(int item, linkedList *list)
{
    // implement item deletion function
    node *ls = list->head;
    while (ls && ls->element != item)
        ls = ls->next;

    if (ls && ls->element == item)
    {
        if (ls == list->cur)
        {
            if (list->cur->next)
                list->cur = list->cur->next;
            else if (list->cur->prev)
                list->cur = list->cur->prev;
            else
            {
                clear(list);
                return;
            }
        }
        if (ls == list->head)
            list->head = list->head->next;
        if (ls == list->tail)
            list->tail = list->tail->prev;
        if (ls->prev)
            ls->prev->next = ls->next;
        if (ls->next)
            ls->next->prev = ls->prev;
        free(ls);
        // print(list);
        return;
    }
    // printf("%d not found\n", item);
}

void swap_ind(int ind1, int ind2, linkedList *list)
{
    // implement swap function
    if(ind1 == ind2)
    {
        // print(list);
        return;
    }
    node *ls1 = list->head, *ls2 = list->head;

    int sz = size(list);
    if (ind1 >= sz || ind2 >= sz)
    {
        printf("Swap: Out of bounds access\n");
        return;
    }

    while (ind1 > 0)
        ls1 = ls1->next, ind1--;
    while (ind2 > 0)
        ls2 = ls2->next, ind2--;

    int temp = ls1->element;
    ls1->element = ls2->element;
    ls2->element = temp;
    // print(list);
}

node *get_head(linkedList *list)
{
    return list->head;
}


void copy(linkedList *sourceList, linkedList *destinationList)
{
    clear(destinationList);
    node *it = get_head(sourceList);
    while(it)
    {
        append(it->element,destinationList);
        it = it->next;
    }
}



// you can define helper functions you need