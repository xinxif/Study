#ifndef SQLIST_H_
#define SQLEST_H_

#define NDEBUG //�رն���

#include<stdint.h>
#include<stdbool.h>
#include<assert.h>
#include<stdlib.h>
#include<string.h>

#define EXTENTION_RATE 2U //�����Ժ����ٶ���չ
typedef int32_t ElemType;
typedef uint32_t Quota;
typedef struct 
{
    //�������ж���Ԫ��
    Quota size;
    //�����п������ɶ���Ԫ��
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