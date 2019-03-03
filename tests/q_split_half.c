#include <assert.h>
#include <stdio.h>

#include "queue.h"


int main(void)
{
    queue_t *q, *a, *b;
    q = q_new();
    a = q_new();
    b = q_new();
    q_insert_tail(q, "a");
    q_insert_tail(q, "b");
    q_insert_tail(q, "c");
    q_insert_tail(q, "d");
    q_insert_tail(q, "e");
    q_split_half(q, a, b);
    assert(q->size == 5);
    assert(a->size == 3);
    assert(b->size == (q->size / 2));
    list_ele_t *ptr;
    ptr = q->head;
    while (ptr != NULL) {
        printf("%s\n", ptr->value);
        ptr = ptr->next;
    }
    ptr = a->head;
    while (ptr != NULL) {
        printf("%s\n", ptr->value);
        ptr = ptr->next;
    }
    ptr = b->head;
    while (ptr != NULL) {
        printf("%s\n", ptr->value);
        ptr = ptr->next;
    }
}
