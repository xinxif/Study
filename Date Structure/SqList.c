#include"SqList.h"

#define ISFULL(X) (X->size==X->capacity)?MoveSqList(X):(void)0;
#define ALLOCATE_MEMORY_ERROR(ARGS,ARGS2 ,MES) ((ARGS) ? (void)0 : DestroyList(ARGS2),fatal_error(MES))



#define SQLIST_DEBUG_ //函数定义中的一些调试

#ifndef SQLIST_DEBUG_
#undef NDEBUG
#include<stdio.h>


#endif

#if defined(_MSC_VER) && !defined(__clang__)
// MSVC编译器环境下使用__declspec(noreturn)
#define NORETURN __declspec(noreturn)
#else
// 其他编译器环境下使用_Noreturn
#define NORETURN _Noreturn
#endif


NORETURN void fatal_error(const char *message)
{
    printf("%s\n", message);

    exit(EXIT_FAILURE);
}

//给顺序表的动态数组分配内存
void MemoryAllocate(SqList *SqLi)
{
    SqList* temp = SqLi;//如果没有成功没配到内存，释放原有的已经分配的

    Quota size = SqLi->size?SqLi->size*EXTENTION_RATE:1U;
    SqLi->element = (ElemType*)calloc(size,sizeof(ElemType));

#if defined(NDEBUG)
    ALLOCATE_MEMORY_ERROR(SqLi,temp, "Allocation Memory Failure");
#else
    assert(SqLi->element);
#endif
    
    SqLi->capacity = size;
}
//移动现有的元素到新分配的内存
static void MoveSqList(SqList* SqLi)
{

    ElemType* temp = SqLi->element;
    MemoryAllocate(SqLi);
    memmove(SqLi->element, temp, sizeof(ElemType)*SqLi->size);
    free(temp);
}
SqList* InitLits(void)
{
    SqList *SqLi = (SqList*)calloc(1,sizeof(SqList));
    assert(SqLi);
    MemoryAllocate(SqLi);
    return SqLi;
}


void DestroyList(SqList *SqLi)
{
#ifndef SQLIST_DEBUG_
    puts("DestroyList Function Debugging:");
    for(int i=0;i<SqLi->size;++i)
    {
        printf("%d ",SqLi->element[i]);
        if (i % 10 == 9)
        {
            putchar('\n');
        }
    }

#endif

    assert(SqLi);
    assert(SqLi->element);

    free(SqLi->element);
    free(SqLi);

    
}
void PushBack(SqList* SqLi, const ElemType element)
{
    //SqList* temp = SqLi;
    if (SqLi->size == SqLi->capacity)
    {
        MoveSqList(SqLi);
    }
    SqLi->element[SqLi->size] = element;
    SqLi->size++;
}
ElemType GetElem(const SqList* SqLi, ElemType location)
{
#ifndef SQLIST_DEBUG_
    printf("GetElem Function Debugging:% d", SqLi->element[location-1]);
#endif // !MTDEBUG

    assert(location <= SqLi->size&&location!=0);
    return SqLi->element[location - 1];
}

void ListInsert(SqList*SqLi,const Quota position, const ElemType elem)
{
#ifndef SQLIST_DEBUG_
    printf("ListInsert Function debuging:%d\n", elem);
#endif // !MYDEBG

    assert(SqLi);
    assert(position <= SqLi->size);//要插入的位置大于数组的大小 执行

    ISFULL(SqLi);

    int32_t real_pos = position - 1;
    for (int i = SqLi->size-1; i >= real_pos; --i)
    {
        SqLi->element[i + 1] = SqLi->element[i];
    }
    SqLi->element[real_pos] = elem;
    ++SqLi->size;
}
ElemType ListDelete(SqList*SqLi, Quota position)
{
    assert(SqLi);
    assert(position <= SqLi->size);

    ISFULL(SqLi);

    int32_t real_pos = position - 1;
    ElemType deleted_val = SqLi->element[real_pos];//返回被删除的元素。
    for (int i = real_pos; i < SqLi->size; ++i)
    {
        SqLi->element[i] = SqLi->element[i + 1];
    }
    --SqLi->size;
    return deleted_val;
}
Quota LocateElem(const SqList*SqLi, ElemType elem)
{
    int32_t temp = (int32_t)SqLi->size;
    for (int i = 0; i < temp; ++i)
    {
        if (SqLi->element[i] == elem)
        {
            return (Quota)i + 1U;
        }
    }
}
