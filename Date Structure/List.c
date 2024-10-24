#include"List.h"
#define RESTORATION(X) ((LinkList*)X)
#define FATAL_ERROR(X) ((X)?((void)0U):(exit(EXIT_FAILURE)))
//List为空指针类型 返回给用户
//head是LNode*
static
LNode* AllocateNewNode(void)
{
	LNode* temp = (LNode*)calloc(1U, sizeof(LNode));
#ifndef NDEBUG
	assert(temp);
#else
	//终结程序，并由操作系统回收分配的内存。
	FATAL_ERROR(temp);
#endif // NDEBUG
	return temp;
}
//找到链表节点的前驱返回
static 
LNode* FindTheNode(LinkList* source,const Quota position)
{
	
	LNode* Current = source->head;
	for (register Quota i = 0U; i < position; ++i)
	{
		Current = Current->next;
	}
	return Current;
}
//辅助函数释放一个节点链接后续的节点
static 
void DelANode(LNode* del_node)
{
	LNode* to_link = NULL;

	if (!del_node->next)
	{
		//如果是最后一个节点什么也不做，通过--size无法访问下一个节点，
		//但还是保存了一个已经释放了的指针的地址
	}
	else
	{
		//因为无法访问上一个节点所以
		//交换数据 然后删除后一个节点而不用户指定的
		ElemType val;
		to_link = del_node;
		val = del_node->next->data;
		to_link->data = val;

		del_node = del_node->next;
		to_link->next = del_node->next;

	}
	free(del_node);
}
List InitList(void)
{
	LinkList* InitializedList = (LinkList *) calloc(1U, sizeof(LinkList));
#ifndef NDEBUG
	assert(InitializedList);
#else
	FATAL_ERROR(InitializedList);
#endif // NDEBUG

	return(List)InitializedList;
}

void ForEach(List list,
	void(*PrintFunc)(const ElemType* const value))
{
	LinkList* temp = RESTORATION(list);//(LinkList*)list;
	LNode *node= temp->head;
	for (register Quota i = 0U; i < temp->size; ++i)
	{
		PrintFunc(&node->data);
		node = node->next;
	}
}

void ListInsert(List destination, const Quota position, const ElemType value)
{
	assert(destination);
	LinkList* temp = RESTORATION(destination);//(LinkList*)destination;
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
	LinkList* OriginalList = RESTORATION(destination);
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
	static Quota Counter = 0U;
#endif // !__LIST_DEBUG__

	LinkList* target = RESTORATION(list);

	LNode* prior = target->head;
	LNode* subsequent = target->head;
	for (Quota i = 0U; i < target->size; ++i)
	{
#ifndef __LIST_DEBUG__
		++Counter;
		printf("释放内存 %"PRID"\n", prior->data);
#endif // !__LIST_DEBUG__
		subsequent = subsequent->next;
		free(prior);
		prior = subsequent;
	}

	free(target);

#ifndef __LIST_DEBUG__
	printf("free了%u次\n", Counter);
#endif // !__LIST_DEBUG__
}
//在指定位置之后插入一个元素
void InsertNextNode(List destination, const Quota position, const ElemType value)
{
	//InsertNextNode(list, 1, 10);
	assert(destination);
	LinkList* temp = RESTORATION(destination);
	assert(position&&position <= temp->size);

	LNode *NewNode = AllocateNewNode();
	LNode *current = FindTheNode(destination, position - 1U);
	
	NewNode->next = current->next;
	current->next = NewNode;

	NewNode->data = value;
	++temp->size;
}

//删除指定位置的节点
void  DeleteNode(List destination, const Quota position)
{
	assert(destination);
	LinkList* temp = RESTORATION(destination);
	assert(position && position <= temp->size);
	
	LNode* del_node = FindTheNode(temp, position - 1U);
	DelANode(del_node);
	--temp->size;
	
}
//删除操作，删除链表destination中第pos位置的元素，返回被删除的元素
ElemType ListDelete(List destination, const Quota position)
{
	ElemType del_val;
	assert(destination);
	LinkList* temp = RESTORATION(destination);
	assert(position <= temp->size);
	LNode* del_node = FindTheNode(temp, position - 1U);
	del_val = del_node->data;
	DelANode(del_node);
	--temp->size;
	return del_val;
}
//按位查找，返回第i个元素
ElemType* GetElem(List list, const Quota position)
{
	assert(list);
	LinkList* temp = RESTORATION(list);
	LNode* found = FindTheNode(temp, position - 1U);
	return &found->data;
}
//按值查找，找到数据域==value的节点,
ElemType* LocateElem(List list, ElemType value,
					bool(*CompareFunc)(const ElemType*const v1,const ElemType *const v2))
{
	assert(list);
	LinkList* temp = RESTORATION(list);
	LNode* node = temp->head;
	ElemType* found=NULL;
	for (; node; node = node->next)
	{
		if (CompareFunc(&node->data, &value))
		{
			found = &node->data;
		}
	}
	return found;
}

void PushBack(List destination, const ElemType value)
{
	//head用来识别是否是同一个链表，如果是，使用以保存的尾节点地址进行尾插操作。
	static LNode* s_tail, * s_head;
	assert(destination);
	LinkList* temp = RESTORATION(destination);
	LNode* NewNode = AllocateNewNode();
	//空表？
	if (!temp->head)
	{
		temp->head =s_head=s_tail = NewNode;
		NewNode->data = value;
		++temp->size;
		return;
	}
	//同一个链表？
	if(s_head!=temp->head)
	{
		s_tail = FindTheNode(temp, temp->size - 1U);
		s_head = temp->head;
	}
	NewNode->data = value;
	s_tail->next = NewNode;

	//更新尾节点地址
	s_tail = NewNode;
	++temp->size;
}