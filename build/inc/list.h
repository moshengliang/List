#ifndef __LIST_H_
#define __LIST_H_

#include <stdio.h>
#include <stdbool.h>

#define LIST_ERR_NONE                   0
#define LIST_ERR_COMMON                 -1
#define LIST_ERR_NULL_LIST              -2       //This error occured, need list_create

typedef struct listNode{
    void *data;
    int size;
    struct listNode *next;
    struct listNode *prev;
}listNode;

typedef struct {
    struct listNode *head;
    int length;
}List;

List *list_create(List **list);
int list_destroy(List *list);
int list_append(void *data, List *list, int size);
int list_prepend(void *data, List *list, int size);
int list_insert(void *data, int i, List *list, int size);
int list_replace(void *data, int i, List *list, int size);
int list_removeAt(int i, List *list);
int list_removeAll(List *list);
bool isEmpty(List *list);
void list_move(int from, int to, List *list);
void list_swap(int i, int j, List *list);
int list_count(List *list);
void *list_data(List *list, int index);
#endif
