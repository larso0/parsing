/*
 * deque.h
 *
 *  Created on: 19. okt. 2015
 *      Author: larso
 */

#ifndef DEQUE_H_
#define DEQUE_H_

typedef struct deque_node
{
    void* value;
    struct deque_node* left;
    struct deque_node* right;
} deque_node;

typedef struct
{
    deque_node* front;
    deque_node* back;
} deque;

deque_node* make_deque_node(void* value);
void free_deque_node(deque_node* node);

deque* make_deque();
void free_deque(deque* dq);
void deque_push_front(deque* dq, void* value);
void deque_push_back(deque* dq, void* value);
void* deque_pop_front(deque* dq);
void* deque_pop_back(deque* dq);

#endif /* DEQUE_H_ */
