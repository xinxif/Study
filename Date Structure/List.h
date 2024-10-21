#ifndef __List_H__
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<assert.h>

//Quota�Ĵ�ӡռλ��
#define PRID PRIu32
//�����������ԣ����Ƿ����ڴ�û���ͷ�
//#define __CPP_DESTRUCTOR__

#ifndef __LIST_DEBUG__
#include<stdio.h>

#endif // !__LIST_DEBUG__

typedef uint32_t Quota;
typedef int32_t ElemType;

//���ص��������ͣ������û���������
typedef void* List;

typedef struct LNode
{
#ifdef __CPP_DESTRUCTOR__
	~LNode()
	{
		puts("LNode�ͷ����\n");
	}
#endif // __CPP_DESTRUCTOR__
	ElemType data;
	struct LNode* next;
}LNode;

typedef struct
{
	Quota size;
	struct LNode *head;

}LinkList;

List InitList(void);
void ListInsert(List destination, const Quota position, const ElemType value);
void PushFront(List destination, const ElemType value);
void DestroyList(List list);
void ForEach(List list,
	void(*PrintFunc)(const ElemType* const value) );
static inline
Quota lenght(const List const list)
{
	return ((LinkList*)list)->size;
}
#endif