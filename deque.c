/*
 * deque.c
 *
 *  Created on: 19. okt. 2015
 *      Author: larso
 */

#include "deque.h"
#include <stdlib.h>

deque_node* make_deque_node(void* value)
{
    deque_node* node = malloc(sizeof(deque_node));
    if(node != NULL)
    {
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void free_deque_node(deque_node* node)
{
    if(node != NULL)
    {
        free(node);
    }
}

deque* make_deque()
{
    deque* dq = malloc(sizeof(deque));
    if(dq != NULL)
    {
        dq->front = NULL;
        dq->back = NULL;
    }
    return dq;
}

void free_deque(deque* dq)
{
    if(dq != NULL)
    {
        deque_node* current = dq->front;
        while(current != NULL)
        {
            deque_node* tmp = current->right;
            free_deque_node(current);
            current = tmp;
        }
        free(dq);
    }
}

void deque_push_front(deque* dq, void* value)
{
    if(dq != NULL)
    {
        deque_node* node = make_deque_node(value);
        if(dq->front != NULL)
        {
            node->right = dq->front;
            dq->front->left = node;
            dq->front = node;
        }
        else
        {
            dq->front = dq->back = node;
        }
    }
}

void deque_push_back(deque* dq, void* value)
{
    if(dq != NULL)
    {
        deque_node* node = make_deque_node(value);
        if(dq->back != NULL)
        {
            node->left = dq->back;
            dq->back->right = node;
            dq->back = node;
        }
        else
        {
            dq->back = dq->front = node;
        }
    }
}

void* deque_pop_front(deque* dq)
{
    void* value = NULL;
    if(dq != NULL && dq->front != NULL)
    {
        value = dq->front->value;
        deque_node* tmp = dq->front->right;
        free_deque_node(dq->front);
        dq->front = tmp;
        if(tmp == NULL)
        {
            dq->back = NULL;
        }
        else
        {
            dq->front->left = NULL;
        }
    }
    return value;
}

void* deque_pop_back(deque* dq)
{
    void* value = NULL;
    if(dq != NULL && dq->back != NULL)
    {
        value = dq->back->value;
        deque_node* tmp = dq->back->left;
        free_deque_node(dq->back);
        dq->back = tmp;
        if(tmp == NULL)
        {
            dq->front = NULL;
        }
        else
        {
            dq->back->right = NULL;
        }
    }
    return value;
}
