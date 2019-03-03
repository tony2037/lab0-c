#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

queue_t *a;
queue_t *b;

int main(void)
{
    a = q_new();
    b = q_new();
    q_insert_tail(a, "a");
    q_insert_tail(a, "b");
    q_insert_tail(a, "c");
    q_insert_tail(b, "d");
    q_insert_tail(b, "e");
    q_insert_tail(b, "f");
    q_insert_tail(b, "g");
    queue_t *r;
    r = sortedqueue_splice(a, b);
    list_ele_t *ptr;
    ptr = r->head;
    int should_be = (int) *"a";
    while (ptr != NULL) {
        assert((int) (ptr->value[0]) == should_be);
        printf("%s\n", ptr->value);
        ptr = ptr->next;
        should_be++;
    }
    q_free(r);
}
