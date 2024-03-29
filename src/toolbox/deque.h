#pragma once
/**
 * @brief 双向链表(deque)数据结构
 */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef void *data_ptr_t;
typedef struct _deque_item_t deque_item_t;

typedef struct _deque_t {
	int cnt;
	struct _deque_item_t {
		void *data;
		deque_item_t *prev;
		deque_item_t *next;
	} *head, *tail;
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
data_ptr_t deque_peek_front(const deque_t *deq);
data_ptr_t deque_peek_back(const deque_t *deq);

int deque_is_empty(const deque_t *deq);

#if defined(ALLOW_FUNC_NAME_ALIASES)
    int is_empty_deque(const deque_t *deq);
#endif

typedef void (*operator_fn_t)(void *node_data, void *extra_arg);
void deque_do_something_for_each_node_in_deque(
	const deque_t *deq, /// 双向链表对象指针
	void *extra_arg, /// 由应用层编写对应函数 fn() 的附加参数
	operator_fn_t fn /// 需要执行的函数名, 函数本身由应用层负责编写
	);

#ifdef __cplusplus
}; /* extern "C" */
#endif /* __cplusplus */
