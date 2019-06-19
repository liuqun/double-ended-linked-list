#include <assert.h>
#include <stdlib.h>
#include "toolbox/deque.h"

struct _deque_item_t {
	void *data;
	deque_item_t *prev;
	deque_item_t *next;
};

deque_t * deque_new(void)
{
	deque_t *deq = (deque_t *)malloc(sizeof(deque_t));
	assert(deq);
	if (!deq) {
		abort();
	}
	deq->cnt = 0;
	deq->head = deq->tail = NULL;

	return deq;
}

void deque_free(deque_t *deq)
{
	deque_item_t *curr; // points to the current node
	deque_item_t *next; //           the next node

	assert(deq);
	curr = deq->head;
	while (curr) {
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(deq);
}

int deque_count_nodes(const deque_t *deq)
{
	assert(deq);
	if (deq->cnt > 0) {
		return (deq->cnt);
	}
	return 0;
}

int is_empty_deque(const deque_t *deq) /// 判断是双向链表否为空
{
	assert(deq);
	return (deque_count_nodes(deq) == 0);
}

int deque_is_empty(const deque_t *deq) /// 函数 deque_is_empty 只是 is_empty_deque 的别名
{
	assert(deq);
	return (deque_count_nodes(deq) == 0);
}

void deque_push_front(deque_t *deq, /*const*/ void *data)
{
	deque_item_t *node;

	assert(deq);

	node = (deque_item_t *)malloc(sizeof(deque_item_t));
	assert(node);
	if (!node) {
		abort();
	}
	node->data = data;
	node->next = deq->head;
	node->prev = NULL;
	deq->cnt += 1;
	if (1 == deq->cnt) {
		deq->head = deq->tail = node;
		return;
	}
	deq->head->prev = node;
	deq->head = node;
}

void deque_push_back(deque_t *deq, /*const*/ void *data)
{
	deque_item_t *node;

	assert(deq);

	node = (deque_item_t *)malloc(sizeof(deque_item_t));
	assert(node);
	if (!node) {
		abort();
	}
	node->data = data;
	node->next = NULL;
	node->prev = deq->tail;
	deq->cnt += 1;
	if (1 == deq->cnt) {
		deq->head = deq->tail = node;
		return;
	}
	deq->tail->next = node;
	deq->tail = node;
}

void deque_pop_front(deque_t *deq)
{
	deque_item_t *first_node;

	assert(deq);
	assert(deq->cnt >= 0);
	if (deq->cnt <= 0) {
		return;
	}

	first_node = deq->head;
	deq->head = first_node->next;
	deq->head->prev = NULL;
	free(first_node);
	deq->cnt -= 1;
	if (deq->cnt <= 0) {
		deq->tail = NULL;
	}
}

void deque_pop_back(deque_t *deq)
{
	deque_item_t *last_node;

	assert(deq);
	assert(deq->cnt >= 0);
	if (deq->cnt <= 0) {
		return;
	}

	last_node = deq->tail;
	deq->tail = last_node->prev;
	deq->tail->next = NULL;
	free(last_node);
	deq->cnt -= 1;
	if (deq->cnt <= 0) {
		deq->head = NULL;
	}
}

data_ptr_t deque_peek_front(const deque_t *deq)
{
	assert(deq);
	return (data_ptr_t) deq->head->data;
}

data_ptr_t deque_peek_back(const deque_t *deq)
{
	assert(deq);
	return (data_ptr_t) deq->tail->data;
}


/* 备注:
 * 以下为迭代器数据结构相关实现代码
 */

#include "toolbox/deque_iterator.h"

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


//样例代码:
//void foobar_do_something_on_each_node(const deque_t *deq)
//{
// void *data;
// deque_iterator_t *iter;
// iter = deque_iterator_new(deq);
// while (!deque_iterator_step_is_end(iter)) {
//	data = deque_iterator_peek(iter);
//	custom_do_something_with_data(data);
//	deque_iterator_step_forward(iter);
// }
// deque_iterator_free(deq);
//
//}//end of foobar
