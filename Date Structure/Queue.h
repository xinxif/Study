#ifndef __QUEUE_H__
#define __QUEUE_H__

#include<stdlib.h>
#include<stdint.h>
#include<inttypes.h>
#include<stdbool.h>

#define NDEBUG
#define __QUEUE_NDEBUG__
#include<assert.h>
#define PRID_FOR_QUEUE  PRId8

#ifndef __QUEUE_NDEBUG__
#include<stdio.h>

#endif // !__QUEUE_NDEBUG__

typedef int8_t elem_type;
typedef void* queue;

typedef struct l_node
{
	elem_type data;
	struct node* next;
}*node, * list;

typedef struct
{
	size_t size;
	list head;
}lst_queue;
queue init(void);
void destroy(queue que);
elem_type* back( queue que);

elem_type* front(queue que);
queue pop(queue que);
queue push(queue que,const elem_type);

static inline
bool empty(queue que)
{
	return !((lst_queue*)que)->size;
}

static inline
size_t size(queue que)
{
	return ((lst_queue*)que)->size;
}
#endif // !__QUEUE_H__

/*
	back()���ʶ�βԪ���ҿ����޸���
	empty()�����Ƿ�Ϊ��
	front()���ʶ���Ԫ���ҿ����޸���
	pop()ɾ������Ԫ��
	push()��Ԫ�ط����β
	size()���еĳ���
*/