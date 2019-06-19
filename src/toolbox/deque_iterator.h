#pragma once

#include "toolbox/deque.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _deque_iterator_t deque_iterator_t;

deque_iterator_t * deque_iterator_new(const deque_t *deq);

data_ptr_t deque_iterator_peek(deque_iterator_t *iter);
void deque_iterator_step_forward(deque_iterator_t *iter);
int deque_iterator_step_is_end(deque_iterator_t *iter);

void deque_iterator_free(deque_iterator_t *iter);

#ifdef __cplusplus
}; /* extern "C" */
#endif /* __cplusplus */
