#include <assert.h>
#include <stdlib.h>
#include "toolbox/deque.h"
#include "toolbox/deque_iterator.h"

/*
 * deque_iterator迭代器数据结构相关实现代码
 */

typedef struct _iternode_t iternode_t;
struct _iternode_t {
	void *data;
	iternode_t *nextnode;
};

struct _deque_iterator_t {
	iternode_t *chain;
};

deque_iterator_t *deque_iterator_new(const deque_t *deq)
{
	deque_iterator_t *iter;

	iter = (deque_iterator_t *)malloc(sizeof(deque_iterator_t));
	assert(iter);
	if (!iter) {
		abort();
	}

	iter->chain = NULL;

	// 对 deque 从末尾向前遍历一圈
	for (deque_item_t *i = deq->tail; i; i = i->prev) {
		iternode_t *chainnode;

		chainnode = (iternode_t *)malloc(sizeof(iternode_t));
		assert(chainnode);
		if (!chainnode) {
			abort();
		}
		chainnode->data = i->data;
		chainnode->nextnode = iter->chain;
		iter->chain = chainnode;
	}

	return iter;
}

data_ptr_t deque_iterator_peek(deque_iterator_t *iter)
{
	if (!iter->chain) {
		return NULL;
	}
	return iter->chain->data;
}

int deque_iterator_step_is_end(deque_iterator_t *iter)
{
	return (NULL == iter->chain);
}

void deque_iterator_step_forward(deque_iterator_t *iter)
{
	iternode_t *tmp;

	if (!iter->chain) {
		return;
	}
	tmp = iter->chain;
	iter->chain = iter->chain->nextnode;
	free(tmp);
}

void deque_iterator_free(deque_iterator_t *iter)
{
	iternode_t *tmp;

	while (iter->chain) {
		tmp = iter->chain;
		iter->chain = iter->chain->nextnode;
		free(tmp);
	}
	free(iter);
	return;
}
