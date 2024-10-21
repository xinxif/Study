#include"List.h"

//ListΪ��ָ������ ���ظ��û�
//head��LNode*
static
LNode* AllocateNewNode(void)
{
	LNode* temp = (LNode*)calloc(1U, sizeof(LNode));
	assert(temp);
	return temp;
}
//�ҵ�����ڵ��ǰ������
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
	//�޷��ŵ�ָ��λ��֮ǰ�����н���Ԫ��λ��
	NewNode->data = Current->data;
	Current->data = value;
	++temp->size;
}
//ͷ��
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
	//	//��������ǿյ�
	//	OriginalList->head = NewNode;
	//}

	//�½ڵ����һ���ڵ�=ԭ�ȵ�ͷ�ڵ�
	NewNode->next = OriginalList->head;
	//ԭ�ȵ�ͷ�ڵ㻻���½ڵ�
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
	printf("free��%u��\n", Counter);
#endif // !__LIST_DEBUG__
}