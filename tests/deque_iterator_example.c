// deque双向链表API冒烟测试
//
// 被测试的API头文件: "toolbox/deque.h" 和 "toolbox/deque_iterator.h"
//
// 编译步骤: 详见项目顶层目录 README 自述文档...
//
// 测试用例描述:
// 1. 创建一个空的双向链表deq;
// 2. 调用push_back操作, 将若干个数据块输入双向链表;
// 3. 执行test_print(), 利用deque_iterator迭代器打印双向链表的内容;
// 4. 对双向链表进行pop操作, 此处掐头去尾各去掉一个数据块;
// 5. 重复一次步骤3, 打印双向链表的内容;

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "toolbox/deque.h"
#include "toolbox/deque_iterator.h"

// 临时定义 my_buffer_t 数据结构, 仅用于存储测试数据
#define MY_BUFFER_DEFAULT_CAPACITY 16
typedef struct _my_buffer_t {
	unsigned long used_bytes;
	unsigned long capacity;
	char data[MY_BUFFER_DEFAULT_CAPACITY];
} my_buffer_t;


// 测试函数test_print(): 利用iterator迭代器工具打印双向链表deq中的所有数据
static
void test_print(const deque_t *deq)
{
	my_buffer_t *p;
	deque_iterator_t *iter;

	iter = deque_iterator_new(deq);
	while (!deque_iterator_step_is_end(iter)) {
		p = (my_buffer_t *) deque_iterator_peek(iter);
		printf("%d bytes, data[]=\"", (int)p->used_bytes);
		for (size_t j = 0; j < p->used_bytes; j++) {
			printf("%c", p->data[j]);
		}
		printf("\"\n");

		deque_iterator_step_forward(iter);
	}
	deque_iterator_free(iter);
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

	// 初始化双向链表deq
	deq = deque_new();

	// 将N组测试数据块插入双向链表deq
	for (size_t i = 0; i < N; i++) {
		deque_push_back(deq, (void *)&(p[i]));
	}

	// 打印deq的内部数据
	printf("deq 内部数据为: {\n");
	test_print(deq);
	printf("}\n");

	// 对双向链表进行pop操作, 此处掐头去尾各去掉一个
	deque_pop_front(deq);
	deque_pop_back(deq);

	// 再次打印deq的内部数据
	printf("掐头去尾之后 deq 内部数据为: {\n");
	test_print(deq);
	printf("}\n");
	// 释放双向链表deq
	deque_free_gracefully(deq);

	// 释放N组buffer数据块
	free(p);
}
