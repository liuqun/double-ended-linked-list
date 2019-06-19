#pragma once
/**
 * @brief 双向链表(deque)数据结构
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef struct _deque_item_t deque_item_t;

typedef struct _deque_t {
	int cnt;
	deque_item_t *head;
	deque_item_t *tail;
} deque_t;

deque_t * deque_new(void);
void deque_free(deque_t *deq);
#define deque_free_gracefully(deq) \
	do { \
		deque_free(deq);\
		deq = NULL; \
	} while (0)

int deque_count_nodes(const deque_t *deq);

void deque_push_front(deque_t *deq, /*const*/ void *data);
void deque_push_back(deque_t *deq, /*const*/ void *data);
void deque_pop_front(deque_t *deq);
void deque_pop_back(deque_t *deq);
void * deque_peek_front(const deque_t *deq);
void * deque_peek_back(const deque_t *deq);

int deque_is_empty(const deque_t *deq);

#if defined(ALLOW_FUNC_NAME_ALIASES)
    int is_empty_deque(const deque_t *deq);
#endif


#ifdef __cplusplus
}; /* extern "C" */
#endif /* __cplusplus */
