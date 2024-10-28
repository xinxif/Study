#include"Stack.h"
static inline
list_stack* restoration(stack stk){return (list_stack*)stk;}
static inline
node get_new_node(void){return (node)calloc(1U, sizeof(struct l_node));}

stack init(void)
{
	list_stack* new_stack = (list_stack*)calloc(1U, sizeof(list_stack));
#ifndef NDEBUG
	assert(new_stack);
#else
	if (!new_stack) exit(EXIT_FAILURE);
#endif // !NDEBUG
	return (stack)new_stack;
}
void destory_stack(stack stk)
{
	assert(stk);
	list_stack* target = restoration(stk);
	node prior, subsequent;
	prior = subsequent = target->head;
	while (prior)
	{
		subsequent = subsequent->next;
#ifndef __STACK_NDEBUG__
		printf("%"PRID" ", prior->data);
#endif 
		free(prior);
		prior = subsequent;
	}
	free(stk);
#ifndef __STACK_NDEBUG__
	putchar('\n');
#endif // !__STACK_NDEBUG__

}
stack push(stack stk, const elem_type data)
{
	list_stack* real_stk = restoration(stk);
	node new_node = get_new_node();
#ifndef NDEBUG
	assert(real_stk && new_node);
#else
	if (!new_node)destory_stack(stk), exit(EXIT_FAILURE);
#endif // !NDEBUG
	new_node->data = data;
	new_node->next = real_stk->head;
	real_stk->head = new_node;
	++real_stk->size;
	return stk;
}
stack pop(stack stk)
{

	assert(stk);
	list_stack *real_stk = restoration(stk);
	if (!real_stk->size)return stk;

	node* new_head = real_stk->head->next;
	node* del_node = real_stk->head;
	real_stk->head = new_head;
	free(del_node);
	--real_stk->size;
	return stk;
}
elem_type* top(const stack stk)
{
	assert(stk);
	return &restoration(stk)->head->data;
}