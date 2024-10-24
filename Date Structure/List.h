#ifndef __List_H__
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<stdbool.h>

//Quota�Ĵ�ӡռλ��
#define PRID PRIu32
#define NDEBUG
#define __LIST_DEBUG__

#include<assert.h>


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
//��ʼ������
List InitList(void);
//�������posλ�ò���value
void ListInsert(List destination, const Quota position, const ElemType value);
//�ڱ�ͷ��һ��Ԫ��
void PushFront(List destination, const ElemType value);
//�ڱ�β��һ��Ԫ��
void PushBack(List destination, const ElemType value);
//��������
void DestroyList(List list);
//��ָ��λ��֮�����һ��Ԫ��
void InsertNextNode(List destination, const Quota position, const ElemType value);
//ɾ��ָ��λ�õĽڵ�
void  DeleteNode(List destination,const Quota position);
//ɾ��������ɾ������destination�е�posλ�õ�Ԫ�أ�del_val=��ɾ����Ԫ��
ElemType ListDelete(List destination, const Quota position);
//��λ���ң����ص�i��Ԫ��,���ظýڵ��������ָ��
ElemType* GetElem(List list, const Quota position);
//��ֵ���ң��ҵ�������==value�Ľڵ㣬���ظýڵ��������ָ��
ElemType* LocateElem(List list, ElemType value,
	bool(*CompareFunc)(const ElemType* const v1, const ElemType* const v2));
//���������������
void ForEach(List list,
	void(*PrintFunc)(const ElemType* const value) );
//����ĳ���
static inline Quota lenght(const List list) {return ((LinkList*)list)->size;}
#endif

//��ָ��λ��֮ǰ����һ��Ԫ�� ��ListInsert���ܳ�ͻ����ʵ��
//void InsertPriorNode();