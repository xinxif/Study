#include"stdalign.h"

alignas(char)
struct person
{
    
    int age;
    const char * name;
};
int main()
{
    return 0;
}