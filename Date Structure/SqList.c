#include"SqList.h"

#ifndef MYDEBUG
#include<stdio.h>


#endif

//给顺序表的动态数组分配内存
void MemoryAllocate(SqList *list)
{
    Limit size = list->size?list->size*EXTENTION_RATE:1;
    list->element = (ElemType*)calloc(size,sizeof(ElemType));
    assert(list->element);
    list->capacity = size;
}

SqList* InitLits(void)
{
    SqList *list = (SqList*)calloc(1,sizeof(SqList));
    assert(list);
    MemoryAllocate(list);
    return list;
}


void DestroyList(SqList *list)
{
#ifndef MYDBUG
    for(int i=0;i<list->size;++i)
    {
        printf("%d",list->element[i]);
    }
#endif
    assert(list);
    assert(list->element);

    free(list->element);
    free(list);

    
}
void PushBack(SqList *list,const ElemType* element)
{
    if(list->size==list->capacity)
    {
        MemoryAllocate(list);
    }
    list->element[list->size-1]=*element;
    list->size++;
}
bool ListInsert(SqList*,Limit,ElemType);
bool ListDelete(SqList*,Limit,ElemType);
Limit LocateElem(const SqList*,ElemType);

