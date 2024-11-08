#include<iostream>
#include<cctype>
#include<string>
#include<vector>
#include<iterator>
#include<cstring>
using namespace std;

int main()
{
    int i = 10;
    double j = 10.;
    i*=static_cast<int>(j);
    cout<<i<<endl;
    return 0;
}