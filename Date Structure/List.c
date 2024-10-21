#include"List.h"

//List为空指针类型 返回给用户
//head是LNode*
static
LNode* AllocateNewNode(void)
{
	LNode* temp = (LNode*)calloc(1U, sizeof(LNode));
	assert(temp);
	return temp;
}
//找到链表节点的前驱返回
static LNode* FindTheNode(LinkList* source,const Quota position)
{
	
	LNode* Current = source->head;
	for (Quota i = 0U; i < position; ++i)
	{
		Current = Current->next;
	}
	return Current;
}
List InitList(void)
{
	LinkList* InitializedList = (LinkList *) calloc(1U, sizeof(LinkList));
	assert(InitializedList);
	return(List)InitializedList;
}

void ForEach(List list,
	void(*PrintFunc)(const ElemType* const value))
{
	LinkList* temp = (LinkList*)list;
	LNode *node= temp->head;
	for (Quota i = 0U; i < temp->size; ++i)
	{
		PrintFunc(&node->data);
		node = node->next;
	}
}

void ListInsert(List destination, const Quota position, const ElemType value)
{
	assert(destination);
	LinkList* temp = (LinkList*)destination;
	assert(position&&position <= temp->size);

	LNode *Current = FindTheNode(temp, position - 1U);
	LNode* NewNode = AllocateNewNode();
	
	NewNode->next = Current->next;
	Current->next = NewNode;
	//无法放到指定位置之前，所有交换元素位置
	NewNode->data = Current->data;
	Current->data = value;
	++temp->size;
}
//头插
void PushFront(List destination, const ElemType value)
{
	assert(destination);
	LinkList* OriginalList = (LinkList*)destination;
	LNode* NewNode = AllocateNewNode();
	
	NewNode->data = value;
	//if (OriginalList->size)
	//{

	//	NewNode->next = OriginalList->head;
	//	OriginalList->head = NewNode;
	//}
	//else
	//{
	//	//如果链表是空的
	//	OriginalList->head = NewNode;
	//}

	//新节点的下一个节点=原先的头节点
	NewNode->next = OriginalList->head;
	//原先的头节点换成新节点
	OriginalList->head = NewNode;
	++OriginalList->size;
	
}
void DestroyList(List list)
{

#ifndef __LIST_DEBUG__
	Quota Counter = 0U;
#endif // !__LIST_DEBUG__

	LinkList* target = (LinkList*)list;

	LNode* prior = target->head;
	LNode* subsequent = target->head;
	for (Quota i = 0U; i < target->size; ++i)
	{
		subsequent = subsequent->next;
		free(prior);
		prior = subsequent;

#ifndef __LIST_DEBUG__
		++Counter;
#endif // !__LIST_DEBUG__

		
	}
	free(target);
#ifndef __LIST_DEBUG__
	printf("free了%u次\n", Counter);
#endif // !__LIST_DEBUG__
}