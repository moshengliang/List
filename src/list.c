#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "version.h"

static struct listNode *mknode(void *data, int size)
{
    struct listNode *new = NULL;
    new = (struct listNode *)malloc(sizeof(struct listNode));
    if (NULL == new)
        return NULL;
    if (NULL != data && 0 != size) {
        new->data = (void *)malloc(size);
        if (data == NULL) {
            free(new);
            return NULL;
        }
        memcpy(new->data, data, size);
    }else {
        new->data = NULL;
    }
    new->size = size;
    new->next = NULL;
    new->prev = NULL;
    return new;
}
/************************************************************* 
 * create a list 
 * initial the head node (default, head node's all pointer are itself)
 ************************************************************/
List *list_create(List **list)
{

    *list = (List *)malloc(sizeof(List));
    if (NULL == *list)
        return NULL;

    struct listNode *head = (struct listNode *)malloc(sizeof(struct listNode));
    if (NULL == head) {
        free(*list);
        return NULL;
    }

    head->next = head;
    head->prev = head;
    head->data = NULL;
    (*list)->head = head;
    (*list)->length = 0;
    return *list;
}

int list_destroy(List *list)
{
    list_removeAll(list);
    free(list->head);
    free(list);
    list = NULL;
    return LIST_ERR_NONE;
}

bool isEmpty(List *list)
{
    return ((list->head->next == list->head) 
            && (list->head->prev == list->head));
}

int list_append(void *data, List *list, int size)
{
    if (NULL == list)
        return LIST_ERR_NULL_LIST; 
    struct listNode *new = mknode(data, size);
    if (new == NULL)
        return LIST_ERR_COMMON;
    list->head->prev->next = new;
    new->prev = list->head->prev;
    new->next = list->head;
    list->head->prev = new;
    list->length++;

    return list->length;
}

int list_prepend(void *data, List *list, int size)
{
    if (NULL == list)
        return LIST_ERR_NULL_LIST;
    list_insert(data, 0, list, size);
    return list->length;

}

int list_insert(void *data, int i, List *list, int size)
{
    struct listNode *p = list->head->next;
    struct listNode *new;
    int index = 0;
    /**/
    for (p = list->head->next; p != list->head; p = p->next)
    {
        if (index == i)
        {
            goto INSERT;
        }else
            index++;
    }
    return -1;

INSERT:
    new = mknode(data, size);
    if (NULL == new)
        return -1;


    new->prev = p->prev;
    new->next = p;
    new->prev->next = new;
    new->next->prev = new;

    list->length++;
    return list->length;
}

int list_replace(void *data, int i, List *list, int size)
{
    struct listNode *p = list->head->next;
    int index = 0;
    /**/
    for (p = list->head->next; p != list->head; p = p->next)
    {
        if (index == i)
        {
            goto REPLACE;
        }else
            index++;
    }

    return -1;
REPLACE:
    if (p->data != NULL)
        free(p);
    p->data = (void *)malloc(size);
    if (p->data == NULL)
    {
        return -1;
    }
    memcpy(p->data, data, size);
    return 0;
}

int list_removeAt(int i, List *list)
{
    struct listNode *p = list->head->next;
    int index = 0;
    for (p = list->head->next; p != list->head; p = p->next)
    {
        if (index == i)
            goto REMOVE;
        else
            index++;
    }

    return -1;
REMOVE:
    p->prev->next = p->next;
    p->next->prev = p->prev;
    if (NULL != p->data)
        free(p->data);
    free(p);
    list->length--;
    return 0;
}

int list_removeAll(List *list)
{
    struct listNode *p;
    for (p = list->head->next; p != list->head; p = p->next) {
        p->prev->next = p->next;
        p->next->prev = p->prev;
        if (NULL != p->data)
            free(p->data);
        free(p);
        list->length--;
    }
    return 0;
}

void *list_data(List *list, int index)
{
    struct listNode *p = NULL;
    int i;
    for (p = list->head->next, i = 0; p != list->head; p = p->next, i++)
    {
        if (i == index)
        {
            return p->data;
        }
    }
    return NULL;
}

void list_move(int from, int to, List *list)
{
    if (from >= list_count(list) || to >= list_count(list))
        return;
    struct listNode *p = NULL, *tmpf = NULL, *tmpt = NULL;
    int i = 0;
    for (p = list->head->next, i = 0; p != list->head && i <= from; p = p->next, i++)
    {
        if (i == from)
        {
            tmpf = p;
        }
    }

    for (p = list->head->next, i = 0; p != list->head && i <= to; p = p->next, i++)
    {
        if (i == to && tmpf != NULL)
        {
            tmpt = p;
            tmpf->prev->next = tmpf->next;
            tmpf->next->prev = tmpf->prev;
            tmpf->prev = tmpt->prev;
            tmpf->next = tmpt;
            tmpt->prev->next = tmpf;
            tmpt->prev = tmpf;
            return;
        }
    }
}

void list_swap(int i, int j, List *list)
{
    if (i >= list_count(list) || j >= list_count(list))
        return;

    struct listNode *p = NULL, *tmpi = NULL, *tmpj = NULL, *swap = NULL;
    int k = 0;
    for (p = list->head->next, k = 0; p != list->head; p = p->next, k++)
    {
        if (k == i)
        {
            tmpi = p;
            if (i >= j)
                goto FOUND_OUT;
        }
        if (k == j) { 
            tmpj = p;
            if (i <= j)
                goto FOUND_OUT;
        }
    }

FOUND_OUT:
    swap = mknode(tmpi->data, tmpi->size);
    memcpy(tmpi->data, tmpj->data, tmpi->size);
    memcpy(tmpj->data, swap->data, tmpi->size);
    free(swap->data);
    free(swap);
    return;
}

int list_count(List *list)
{
    if (NULL == list)
        return 0;
    return list->length;
}
