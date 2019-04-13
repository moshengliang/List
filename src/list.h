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
/*
 * create a list;
 */
List *list_create(List **list);

/*
 * destroy a list
 */
int list_destroy(List *list);

/*
 * append data into the list.
 */
int list_append(void *data, List *list, int size);

/*
 * prepend data into the list
 */
int list_prepend(void *data, List *list, int size);

/*
 * insert data into the specified location.
 */
int list_insert(void *data, int i, List *list, int size);

/*
 * replace the data at the specified location.
 */
int list_replace(void *data, int i, List *list, int size);

/*
 * remove the data at specified location.
 */
int list_removeAt(int i, List *list);

/*
 * clear all the data
 */
int list_removeAll(List *list);

/*
 * check if the list is empty
 */
bool isEmpty(List *list);

/*
 * move data from a location to another location.
 */
void list_move(int from, int to, List *list);

/*
 * exchange the data
 */
void list_swap(int i, int j, List *list);

/*
 * get the data count at the list.
 */
int list_count(List *list);

/*
 * read data from the list.
 */
void *list_data(List *list, int index);
#endif
