// deque双向链表API冒烟测试
//
// 被测试的API头文件: "toolbox/deque.h"
//
// 编译步骤: 详见项目顶层目录 README 自述文档...
//
// 测试用例设计思路:
// 1. 创建一个空的双向链表deq;
// 2. 调用push_back操作, 将若干个数据块输入双向链表;
// 3. 执行test_print(), 遍历双向链表deque结构体内部所有节点, 打印全部内容;
// 4. 对双向链表进行pop操作, 此处掐头去尾各去掉一个数据块;
// 5. 重复一次步骤3, 打印双向链表的内容;
// 6. 对双向链表执行1次push_front操作, 恢复之前的头节点;
// 7. 重复一次步骤3, 打印双向链表的内容;
// 8. 对双向链表再执行1次push_front操作, 插一个节点到双向链表头部;
// 9. 重复一次步骤3, 打印双向链表的内容;
// 最后: 释放为测试用例分配的所有内存


#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "toolbox/deque.h"

// 临时定义 my_buffer_t 数据结构, 仅用于存储测试数据
#define MY_BUFFER_DEFAULT_CAPACITY 16
typedef struct _my_buffer_t {
	unsigned long used_bytes;
	unsigned long capacity;
	char data[MY_BUFFER_DEFAULT_CAPACITY];
} my_buffer_t;


// 测试函数test_print(): 利用do_something_for_each_node_in_deque()函数打印双向链表deq中的所有数据
static
void test_print(const deque_t *deq)
{
	unsigned long i;
	deque_item_t *node;
	my_buffer_t *p;

	// 从头到尾, 遍历deque每个节点
	for (node = deq->head; node; node = node->next) {
		p = node->data;
		printf("%lu, %lu, {", p->used_bytes, p->capacity);
		for (i = 0; i < p->used_bytes; i++) {
			printf("%c", p->data[i]);
		}
		printf("}\n");
	}
}

int main()
{
	deque_t *deq; // 双向链表 deq 即 double-ended-queue
	my_buffer_t *p;
	const size_t N = 5;

	// 初始化N组buffer数据块备用
	p = (my_buffer_t *)calloc(sizeof(struct _my_buffer_t), N);
	for (size_t i = 0; i < N; i++) {
		p[i].capacity = MY_BUFFER_DEFAULT_CAPACITY;
		p[i].used_bytes = i+1;
		for (size_t j = 0; j < p[i].used_bytes; j++) {
			p[i].data[j] = 'A' + i;
		}
	}

	// 1. 初始化双向链表deq
	deq = deque_new();

	// 2. 将N组测试数据块插入双向链表deq
	for (size_t i = 0; i < N; i++) {
		deque_push_back(deq, (void *)&(p[i]));
	}

	// 3. 打印deq的内部数据
	printf("deq 内部数据为: {\n");
	test_print(deq);
	printf("}\n");

	// 4. 对双向链表进行pop操作, 此处掐头去尾各去掉一个
	deque_pop_front(deq);
	deque_pop_back(deq);

	// 5. 再次打印deq的内部数据
	printf("掐头去尾之后 deq 内部数据为: {\n");
	test_print(deq);
	printf("}\n");

	// 6. 对双向链表的头进行一次push操作, 还原原来的头结点
	deque_push_front(deq, &p[0]);

	// 7. 再次打印deq的内部数据
	printf("恢复头部之后 deq 内部数据为: {\n");
	test_print(deq);
	printf("}\n");

	// 8. 对双向链表的头进行一次push操作, 把之前的尾结点强行装在头部
	deque_push_front(deq, &p[N-1]);

	// 9. 再次打印deq的内部数据
	printf("头部再插入一个点之后 deq 内部数据为: {\n");
	test_print(deq);
	printf("}\n");

	/* 最后释放测试用到的内存 */
	// 释放双向链表deq
	deque_free_gracefully(deq);

	// 释放N组buffer数据块
	free(p);
}
