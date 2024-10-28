#include"Queue.h"
#define FATAL_ERROR(X)((X)?(void)0:free(X))

static inline lst_queue* restoration(queue que)	{return (lst_queue*)que;}

static node* add_node(void)
{
	node* new_node = calloc(1U, sizeof(struct l_node));
#ifndef NDEBUG
	assert(new_node);
#else
	FATAL_ERROR(new_node);
#endif // !NDEBUG
	return new_node;
}

queue init(void)
{
	lst_queue* initialized = calloc(1U, sizeof(lst_queue));
#ifndef NDEBUG
	assert(initialized);
#else
	FATAL_ERROR(initialized);
#endif // !NDEBUG
	return (queue)initialized;
}
void destroy(queue que)
{
	assert(que);
	lst_queue* real_que = restoration(que);
	node prior, subsequent;
	prior = subsequent = real_que->head;
	while (prior)
	{
		subsequent = subsequent->next;
		
#ifndef __QUEUE_NDEBUG__
		printf("destroy test%"PRID_FOR_QUEUE"\t", prior->data);
#endif // !__QUEUE_NDEBUG__
		free(prior);
		prior = subsequent;
	}
	free(que);
}
elem_type* back(queue que)
{
	assert(que);
	lst_queue* real_que = restoration(que);

#ifndef NDEBUG
	assert(real_que->size);
#endif // !NDEBUG
	node tail = real_que->head;
	while (tail->next)
	{
		tail = tail->next;
	}
#ifdef NDEBUG
	//空队列返回0
	if (!real_que->size)
	{
		return &real_que->size;
	}
#endif // NDEBUG

	return &tail->data;
}
elem_type* front(queue que)
{
#ifndef __QUEUE_NDEBUG__
	static size_t counter;
	++counter;
	printf("%u ", counter);
#endif // !__QUEUE_NDEBUG__

	assert(que);
	lst_queue *real_que = restoration(que);
#ifdef NDEBUG
	//空队列返回0
	if (!real_que->size)
	{
		return &real_que->size;
	}
#endif // NDEBUG
	return &real_que->head->data;
}
queue pop(queue que)
{
	assert(que);
	lst_queue* real_que = restoration(que);
	if (!real_que->size) return que;

	node del_node = real_que->head;
	node new_head = real_que->head->next;
	real_que->head = new_head;

	--real_que->size;
#ifndef __QUEUE_NDEBUG__
	printf("pop test%"PRID_FOR_QUEUE" ", del_node->data);
#endif // !__QUEUE_NDEBUG__
	free(del_node);
	return que;
}

queue push(queue que,const elem_type val)
{
	assert(que);
	lst_queue* real_que = restoration(que);
	node new_node = add_node();
	static node s_head, s_tail;
	//空表
	if (!real_que->head)
	{
		real_que->head = s_head = s_tail = new_node;
		new_node->data = val;
		++real_que->size;
		return que;
	}
	//同一个队列
	if (s_head != real_que->head)
	{
		s_tail=s_head = real_que->head;
		while (s_tail->next)
		{
			s_tail = s_tail->next;
		}
	}
	new_node->data = val;
	s_tail->next = new_node;

	s_tail = new_node;
	++real_que->size;
	return que;
}
