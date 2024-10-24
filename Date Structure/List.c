#include"List.h"
#define RESTORATION(X) ((LinkList*)X)
#define FATAL_ERROR(X) ((X)?((void)0U):(exit(EXIT_FAILURE)))
//ListΪ��ָ������ ���ظ��û�
//head��LNode*
static
LNode* AllocateNewNode(void)
{
	LNode* temp = (LNode*)calloc(1U, sizeof(LNode));
#ifndef NDEBUG
	assert(temp);
#else
	//�ս���򣬲��ɲ���ϵͳ���շ�����ڴ档
	FATAL_ERROR(temp);
#endif // NDEBUG
	return temp;
}
//�ҵ�����ڵ��ǰ������
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
//���������ͷ�һ���ڵ����Ӻ����Ľڵ�
static 
void DelANode(LNode* del_node)
{
	LNode* to_link = NULL;

	if (!del_node->next)
	{
		//��������һ���ڵ�ʲôҲ������ͨ��--size�޷�������һ���ڵ㣬
		//�����Ǳ�����һ���Ѿ��ͷ��˵�ָ��ĵ�ַ
	}
	else
	{
		//��Ϊ�޷�������һ���ڵ�����
		//�������� Ȼ��ɾ����һ���ڵ�����û�ָ����
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
	//�޷��ŵ�ָ��λ��֮ǰ�����н���Ԫ��λ��
	NewNode->data = Current->data;
	Current->data = value;
	++temp->size;
}
//ͷ��
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
	static Quota Counter = 0U;
#endif // !__LIST_DEBUG__

	LinkList* target = RESTORATION(list);

	LNode* prior = target->head;
	LNode* subsequent = target->head;
	for (Quota i = 0U; i < target->size; ++i)
	{
#ifndef __LIST_DEBUG__
		++Counter;
		printf("�ͷ��ڴ� %"PRID"\n", prior->data);
#endif // !__LIST_DEBUG__
		subsequent = subsequent->next;
		free(prior);
		prior = subsequent;
	}

	free(target);

#ifndef __LIST_DEBUG__
	printf("free��%u��\n", Counter);
#endif // !__LIST_DEBUG__
}
//��ָ��λ��֮�����һ��Ԫ��
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

//ɾ��ָ��λ�õĽڵ�
void  DeleteNode(List destination, const Quota position)
{
	assert(destination);
	LinkList* temp = RESTORATION(destination);
	assert(position && position <= temp->size);
	
	LNode* del_node = FindTheNode(temp, position - 1U);
	DelANode(del_node);
	--temp->size;
	
}
//ɾ��������ɾ������destination�е�posλ�õ�Ԫ�أ����ر�ɾ����Ԫ��
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
//��λ���ң����ص�i��Ԫ��
ElemType* GetElem(List list, const Quota position)
{
	assert(list);
	LinkList* temp = RESTORATION(list);
	LNode* found = FindTheNode(temp, position - 1U);
	return &found->data;
}
//��ֵ���ң��ҵ�������==value�Ľڵ�,
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
	//head����ʶ���Ƿ���ͬһ����������ǣ�ʹ���Ա����β�ڵ��ַ����β�������
	static LNode* s_tail, * s_head;
	assert(destination);
	LinkList* temp = RESTORATION(destination);
	LNode* NewNode = AllocateNewNode();
	//�ձ�
	if (!temp->head)
	{
		temp->head =s_head=s_tail = NewNode;
		NewNode->data = value;
		++temp->size;
		return;
	}
	//ͬһ������
	if(s_head!=temp->head)
	{
		s_tail = FindTheNode(temp, temp->size - 1U);
		s_head = temp->head;
	}
	NewNode->data = value;
	s_tail->next = NewNode;

	//����β�ڵ��ַ
	s_tail = NewNode;
	++temp->size;
}