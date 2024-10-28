
/*
	empty()链是否为空
	pop()弹出栈顶元素
	push()把元素压入栈顶
	size()栈的大小
	top()访问栈顶的元素
	init()初始化栈
	destory_stack()释放栈
*/
#ifndef __STACK__
#define __STACK__
#include<stdlib.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>

#undef NDEBUG
#define NDEBUG
#define __STACK_NDEBUG__

#include<assert.h>
#define PRID PRId32

#ifndef __STACK_NDEBUG__
#include<stdio.h>
#endif // !__STACK_NDEBUG__

typedef void* stack;
typedef int32_t elem_type;

typedef struct l_node
{
	elem_type data;
	struct node* next;
}*node,*list;

typedef struct
{
	size_t size;
	list head;
}list_stack;

stack init(void);
stack push(stack stk,const elem_type data);
stack pop(stack stk);
elem_type* top(const stack stk);
void destory_stack(stack stk);
static inline
size_t size(const stack stk) { return ((list_stack*)stk)->size;}
static inline
bool empty(const stack stk) { return !((list_stack*)stk)->size;}

#endif // !__STACK__

