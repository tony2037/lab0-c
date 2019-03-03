/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
        return NULL;
    memset(q, 0, sizeof(queue_t));
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL) {
        return;
    }
    list_ele_t *tmp = q->head;
    list_ele_t *prev = q->head;
    while (tmp != NULL) {
        if (tmp->value != NULL) {
            free(tmp->value);
        }
        prev = tmp;
        tmp = tmp->next;
        free(prev);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        printf("Allocate failed\n");
        return false;
    }
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    memset(newh, 0, sizeof(list_ele_t));
    newh->value = malloc(sizeof(char) * strlen(s) + 1);
    if (newh->value == NULL) {
        printf("Allocate failed\n");
        free(newh);
        return false;
    }
    memset(newh->value, 0, sizeof(char) * strlen(s) + 1);
    strcpy(newh->value, s);

    if (q->size == 0) {
        newh->next = NULL;
        q->head = newh;
        q->tail = newh;
        q->size++;
        return true;
    }

    newh->next = q->head;
    q->head = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return false;
    }
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }
    memset(newh, 0, sizeof(list_ele_t));
    newh->value = malloc(sizeof(char) * strlen(s) + 1);
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    memset(newh->value, 0, sizeof(char) * strlen(s) + 1);
    strcpy(newh->value, s);
    if (q->size == 0) {
        /* This implies that the queue is empty */
        newh->next = NULL;
        q->head = newh;
        q->tail = newh;
        q->size++;
        return true;
    }

    newh->next = NULL;
    q->tail->next = newh;
    q->tail = newh;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL) {
        return false;
    }
    if (q->head == NULL) {
        return false;
    }

    if (sp != NULL) {
        memset(sp, (int) '\0', bufsize);
        strncpy(sp, q->head->value, bufsize - 1);
    }
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return 0;
    }
    if (q->head == NULL) {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q != NULL && q->head != NULL && q->head->next != NULL) {
        list_ele_t *cur = q->head->next;
        list_ele_t *prec;
        q->tail = q->head;
        while (cur != NULL) {
            prec = cur->next;
            cur->next = q->head;
            q->head = cur;
            cur = prec;
        }
        q->tail->next = NULL;
    }
}

/*
 * Assume the two given queues have been sorted.
*/
queue_t *sortedqueue_splice(queue_t *a, queue_t *b)
{
    if (a == NULL) {
        return b;
    }
    if (b == NULL) {
        return a;
    }

    queue_t *new_h = q_new();
    list_ele_t *ptr_a = a->head;
    list_ele_t *ptr_b = b->head;
    while (1) {
        int cmp = strcmp(ptr_a->value, ptr_b->value);
        if (cmp < 0) {
            q_insert_tail(new_h, ptr_a->value);
            ptr_a = ptr_a->next;
        } else if (cmp == 0) {
            q_insert_tail(new_h, ptr_a->value);
            q_insert_tail(new_h, ptr_b->value);
            ptr_a = ptr_a->next;
            ptr_b = ptr_b->next;
        } else if (cmp > 0) {
            q_insert_tail(new_h, ptr_b->value);
            ptr_b = ptr_b->next;
        }

        if (!ptr_a) {
            /* Now queue a should be done. */
            q_free(a);
            while (ptr_b) {
                q_insert_tail(new_h, ptr_b->value);
                ptr_b = ptr_b->next;
            }
            q_free(b);
            break;
        }

        if (!ptr_b) {
            q_free(b);
            /* Now queue b should be done. */
            while (ptr_a) {
                q_insert_tail(new_h, ptr_a->value);
                ptr_a = ptr_a->next;
            }
            q_free(a);
            break;
        }
    }

    return new_h;
}

/*
 * Using merge sorting algorithm to sort the given queue
*/
queue_t *merge_sort(queue_t *q)
{
    queue_t *ptr;
    ptr = q;
    if (q == NULL)
        return NULL;
    if (q->size == 0 || q->size == 1)
        return q;
    queue_t *a, *b;
    a = q_new();
    b = q_new();
    q_split_half(ptr, a, b);
    a = merge_sort(a);
    b = merge_sort(b);
    return sortedqueue_splice(a, b);
}

/*
 * Split the given queue at the middle into two queues
 * Assume a & b should be initialized already.
*/
void q_split_half(queue_t *q, queue_t *a, queue_t *b)
{
    if (q == NULL) {
        a = NULL;
        b = NULL;
        return;
    }
    if (q->size == 1) {
        a = NULL;
        b = NULL;
        return;
    }
    if (a == NULL || b == NULL || a->size != 0 || b->size != 0) {
        q_free(a);
        q_free(b);
        a = NULL;
        b = NULL;
        return;
    }
    int split_point = q->size / 2;
    list_ele_t *sp; /* Stand for split point*/
    sp = q->head;
    while (split_point--) {
        sp = sp->next;
    }
    list_ele_t *ptr;
    ptr = q->head;
    while (ptr != sp) {
        q_insert_tail(a, ptr->value);
        ptr = ptr->next;
    }
    while (ptr != NULL) {
        q_insert_tail(b, ptr->value);
        ptr = ptr->next;
    }

}
