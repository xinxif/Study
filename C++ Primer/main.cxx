#include<iostream>
#include<cctype>
#include<string>
#include<vector>
using namespace std;
int main()
{
    vector<unsigned>scores(11,0);
    unsigned grade;
    while (cin>>grade)
    {
        if(grade<=100)
            ++*(scores.begin()+grade/10);
    }
    for(const auto &val:scores)
    {
        cout<<val<<" ";
    } 
    return 0;
}