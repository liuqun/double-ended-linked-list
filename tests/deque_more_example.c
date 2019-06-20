// deque双向链表API冒烟测试
//
// 被测试的API头文件: "toolbox/deque.h"
//
// 编译步骤: 详见项目顶层目录 README 自述文档...
//
// 测试用例描述:
// 1. 创建一个空的双向链表deq;
// 2. 调用push_back操作, 将若干个数据块输入双向链表;
// 3. 执行test_print(), 遍历双向链表所有节点, 打印内容;
// 4. 对双向链表进行pop操作, 此处掐头去尾各去掉一个数据块;
// 5. 重复一次步骤3, 打印双向链表的内容;

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


typedef struct _my_test_extra_arg_t {
	// 此处, 由用户层应用定制专用参数
	FILE *fp;//print_one_buffer()函数需要这个参数, 以确定打印到屏幕还是打印到文本文件.
} my_test_extra_arg_t;


static
void print_one_buffer(void *data, void *extra_arg)
{
	size_t i = 0;

	my_buffer_t *p = (my_buffer_t *) data;
	my_test_extra_arg_t *my_arg = (my_test_extra_arg_t *)extra_arg;

	#define DEFAULT_FP stdout
	FILE *fp = DEFAULT_FP;
	if (NULL != my_arg->fp) {
		fp = my_arg->fp;
	}
	fprintf(fp, "%lu, %lu, {", p->used_bytes, p->capacity);
	for (i = 0; i < p->used_bytes; i++) {
		fprintf(fp, "%c", p->data[i]);
	}
	fprintf(fp, "}\n");
}

// 测试函数test_print(): 利用do_something_for_each_node_in_deque()函数打印双向链表deq中的所有数据
static
void test_print(const deque_t *deq)
{
	my_test_extra_arg_t extra_test_arg;

	extra_test_arg.fp = stdout;
	deque_do_something_for_each_node_in_deque(deq, &extra_test_arg, print_one_buffer);
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
