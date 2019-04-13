#include <unistd.h>
#include "list.h"

List *list = NULL;

struct int_data {
    int id;
};

void list_display(List *list)
{
    int i = 0;
    printf("%s %d\n", __FUNCTION__, list_count(list));
#if 0
    struct listNode *p;
    for (p = list->head->next; p != list->head; p = p->next)
    {
        printf("pointer %p %d\n", p, *(int *)(p->data));
    }
#else

    for (i = 0; i < list_count(list); i++)
    {
        int *d = list_data(list, i);
        printf("data = %d, %d\n", *d, i);
    }
#endif
}

int main(int argc, char **argv)
{
    int i, j;
    list = list_create(&list);
    struct int_data data;
    for (i = 0; i < 10; i++)
    {
        printf("id = %d\n", i);
        list_append((void *)&i, list, sizeof(int));
        list_display(list);
    }

    for (j = 20; j > 12; j--)
    {
        list_prepend((void *)&j, list, sizeof(int));
        list_display(list);
    }

    printf("insert -----\n");
    for (j = 30; j < 40; j++)
    {
        list_insert((void *)&j, 4, list, sizeof(int));
        list_display(list);
    }

    printf("swap ------\n");
    list_swap(0, 2, list);
    list_display(list);


    printf("move ------\n");
    list_move(0, list_count(list) - 1, list);
    list_display(list);

    printf("remove at index\n");
    for (i = 0; i < 10; i++) {
        list_removeAt(0, list);
        list_display(list);
    }

    printf("re append -----\n");
    int v = 99;
    list_append(&v, list, sizeof(int));
    list_display(list);

    printf("remove all\n");
    list_removeAll(list);
    list_display(list);


    list_append(&v, list, sizeof(int));
    list_display(list);

    printf("isEmpty ? %d\n", isEmpty(list));


    while(1);
        usleep(100);
}
