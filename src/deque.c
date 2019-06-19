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

void * deque_peek_front(const deque_t *deq)
{
	assert(deq);
	return (void *) deq->head->data;
}

void * deque_peek_back(const deque_t *deq)
{
	assert(deq);
	return (void *) deq->tail->data;
}
