vpath %.c src
vpath %.h src/toolbox

# 1. 编译器
CC = gcc
CXX = g++

# 2. C/C++编译器通用选项
CFLAGS = -Wall -Wextra
CXXFLAGS = $(CFLAGS)

# 3. 项目目录结构定义
# gcc编译器要求使用-I选项指定头文件路径
# 当前项目为了结构简单，所以头文件和源文件均存储在src目录下
# 注：Makefile中的CPPFLAGS是gcc C语言编译器的Pre Processor预处理选项，而CXXFLAGS才是C++编译选项
TOPDIR = .
SRCDIR = src
CPPFLAGS = -I$(SRCDIR) -I$(TOPDIR)/include

# 4. 判断当前启用debug调试模式还是release模式
MODE := debug
ifeq ($(MODE),debug)
 CFLAGS += -g
 CPPFLAGS += -DPACKAGE_BUILD_MODE="debug"
else
 CPPFLAGS += -DNDEBUG
 CPPFLAGS += -DPACKAGE_BUILD_MODE="release"
endif

# 手动维护下列源代码文件清单
HEADER_LIST += deque.h
SOURCE_LIST += deque.c
HEADER_LIST += deque_iterator.h
SOURCE_LIST += deque_iterator.c
OBJECT_LIST = $(patsubst %.c,%.o,$(SOURCE_LIST))

.PHONY: all
# 顶层依赖关系
all: $(OBJECT_LIST) selftest
%.o: %.c %.h
	$(COMPILE.c) -o $@ $<
%.o: %.c
	$(COMPILE.c) -o $@ $<
.PHONY: clean
clean:
	$(RM) *.o
	$(RM) deque_*_example
.PHONY: selftest
selftest: deque_basic_example deque_iterator_example
deque_basic_example: deque_basic_example.o deque.o
	$(LINK.o) -o $@ $^ $(LIBS)
deque_iterator_example: deque_iterator_example.o $(OBJECT_LIST)
	$(LINK.o) -o $@ $^ $(LIBS)
vpath %.c tests
