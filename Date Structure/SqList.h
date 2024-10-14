#ifndef SQLIST_H_
#define SQLEST_H_
#include<stdint.h>
#include<stdbool.h>
#include<assert.h>
#include<stdlib.h>

#define EXTENTION_RATE 2
typedef int32_t ElemType;
typedef uint32_t Limit;
typedef struct 
{
    Limit size;
    Limit capacity;
    ElemType *element;
}SqList;

SqList* InitLits(void);
void DestroyList(SqList *);
bool ListInsert(SqList*,Limit,ElemType);
bool ListDelete(SqList*,Limit,ElemType);
Limit LocateElem(const SqList*,ElemType);
void PushBack(SqList *list,const ElemType* element);
inline static
ElemType GetElem(const SqList* list,ElemType location)  
{
    assert(location<=list->size);
    return *(list->element);
}



#endif