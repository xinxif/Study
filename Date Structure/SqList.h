#ifndef SQLIST_H_
#define SQLEST_H_

#define NDEBUG //关闭断言

#include<stdint.h>
#include<stdbool.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

#define EXTENTION_RATE 2U //数组以何种速度扩展
typedef int32_t ElemType;
typedef uint32_t Quota;
typedef struct 
{
    //数组中有多少元素
    Quota size;
    //数组中可以容纳多少元素
    Quota capacity;
    ElemType *element;
}SqList;

SqList* InitLits(void);
void DestroyList(SqList *SqLi);
void ListInsert(SqList*destination,const Quota position,const ElemType element);
ElemType ListDelete(SqList* SqLi, Quota position);
Quota LocateElem(const SqList*SqLi,ElemType element);
void PushBack(SqList *SqLi,const ElemType element);
ElemType GetElem(const SqList* SqLi, ElemType location);
inline static
Quota Size(const SqList* SqLi) { return SqLi->size; }


#endif