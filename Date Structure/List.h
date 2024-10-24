#ifndef __List_H__
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<stdbool.h>

//Quota的打印占位符
#define PRID PRIu32
#define NDEBUG
#define __LIST_DEBUG__

#include<assert.h>


//析构函数测试，看是否有内存没有释放
//#define __CPP_DESTRUCTOR__

#ifndef __LIST_DEBUG__
#include<stdio.h>

#endif // !__LIST_DEBUG__

typedef uint32_t Quota;
typedef int32_t ElemType;

//返回的数据类型，不让用户访问数据
typedef void* List;

typedef struct LNode
{
#ifdef __CPP_DESTRUCTOR__
	~LNode()
	{
		puts("LNode释放完成\n");
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
//初始化链表
List InitList(void);
//在链表的pos位置插入value
void ListInsert(List destination, const Quota position, const ElemType value);
//在表头放一个元素
void PushFront(List destination, const ElemType value);
//在表尾放一个元素
void PushBack(List destination, const ElemType value);
//销毁链表
void DestroyList(List list);
//在指定位置之后插入一个元素
void InsertNextNode(List destination, const Quota position, const ElemType value);
//删除指定位置的节点
void  DeleteNode(List destination,const Quota position);
//删除操作，删除链表destination中第pos位置的元素，del_val=被删除的元素
ElemType ListDelete(List destination, const Quota position);
//按位查找，返回第i个元素,返回该节点数据域的指针
ElemType* GetElem(List list, const Quota position);
//按值查找，找到数据域==value的节点，返回该节点数据域的指针
ElemType* LocateElem(List list, ElemType value,
	bool(*CompareFunc)(const ElemType* const v1, const ElemType* const v2));
//遍历链表的数据域
void ForEach(List list,
	void(*PrintFunc)(const ElemType* const value) );
//链表的长度
static inline Quota lenght(const List list) {return ((LinkList*)list)->size;}
#endif

//在指定位置之前插入一个元素 与ListInsert功能冲突不做实现
//void InsertPriorNode();