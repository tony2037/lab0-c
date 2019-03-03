#include <assert.h>
#include <stdio.h>

#include "queue.h"


int main(void)
{
    queue_t *q, *sorted_q;
    q = q_new();
    q_insert_tail(q, "a");
    q_insert_tail(q, "g");
    q_insert_tail(q, "c");
    q_insert_tail(q, "b");
    q_insert_tail(q, "e");
    q_insert_tail(q, "f");
    q_insert_tail(q, "d");
    list_ele_t *ptr;
    ptr = q->head;
    printf("q: ===============\n");
    while (ptr != NULL) {
        printf("%s\n", ptr->value);
        ptr = ptr->next;
    }
    sorted_q = merge_sort(q);
    int should_be = (int) *"a";
    ptr = sorted_q->head;
    printf("merge sort: ===============\n");
    while (ptr != NULL) {
        printf("%s\n", ptr->value);
        assert(ptr->value[0] == should_be++);
        ptr = ptr->next;
    }
}
