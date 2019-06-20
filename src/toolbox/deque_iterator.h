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

// 附录: 迭代器的用法demo样例代码
//
// void app_do_something_for_each_node_of_deque(const deque_t *deq)
// {
// 	void *data;
// 	deque_iterator_t *iter;
// 	iter = deque_iterator_new(deq);
// 	while (!deque_iterator_step_is_end(iter)) {
// 		data = deque_iterator_peek(iter);
// 		app_do_something_with_data(data/*, more extra args...*/);
// 		deque_iterator_step_forward(iter);
// 	}
// 	deque_iterator_free(deq);
// }
