#include<stdio.h>
#include<math.h>
#include<stdint.h>
#include<iso646.h>
#include<conio.h>
union hold
{
    int8_t i;
    int_fast16_t j;
    int_least32_t k;
    int64_t m;
};
void test(x,y,z)
int x,y,z;
{
    printf("%d %d %d",x,y,z);
}
int main(void)
{
    //fputs()
    float const *pfc;
    float*const pfb;
    (int []){1,2};
    printf("%zu",sizeof(union hold));
    return 0;
}