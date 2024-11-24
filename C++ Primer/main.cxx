#include<iostream>
#include<vector>
#include<algorithm>
#include<list>
#include<string>
#include<functional>
#include<iterator>
#include<cstdlib>
#include<fstream>
#define c std::cout
#define e std::endl
using std::placeholders::_1;
template <typename ty>
void print(const ty&val)
{
    std::cout<<val<<" ";
}
bool check_size(const std::string &s,const std::string::size_type sz)
{
    return !(s.size()>=sz);
}
void classify(std::ostream_iterator<int>&cEven,std::ostream_iterator<int>&cOdd,const int val)
{
    if(val&0x1)
        cOdd=val;
    else
        cEven=val;
}
int main(int argc,char **argv)
{
    if(argc<3)
    {
        std::cerr<<"three files are needed";
        return EXIT_FAILURE;
    }
    std::ifstream in(argv[1]);
    std::ofstream even(argv[2],std::ofstream::app),odd(argv[3],std::ostream::app);
    if(!(in.is_open()&&even.is_open()&&odd.is_open()))
    {
        std::cerr<<"fail to open files";
        return EXIT_FAILURE;
    }
    std::istream_iterator<int> iCin(in),iEof;
    std::ostream_iterator<int> cEven(even," "),cOdd(odd,"\n");
    std::for_each(iCin,iEof,std::bind(classify,cEven,cOdd,std::placeholders::_1));
    return 0;
}