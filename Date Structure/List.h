#ifndef __List_H__
#include<stdint.h>
#include<inttypes.h>
#include<stdlib.h>
#include<assert.h>

//Quota的打印占位符
#define PRID PRIu32
//析构函数测试，看是否又内存没有释放
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