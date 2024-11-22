#include<iostream>
#include<vector>
#include<string>
#include<deque>
void print(std::vector<int>&vec,std::vector<int>::size_type index)
{

	if(index<vec.size())
	{
		std::cout<<vec[index]<<' ';
		print(vec,index+1);
	}
}

int sum(int x,int y){return x+y;}
int minus(int x,int y){return x-y;}
int multiply(int x,int y){return x*y;}
int division(int x,int y){return x/y;}
decltype(division)*re_div(int x,int y){return &division;}
auto re_mul(int x,int y)->int(*)(int,int)
{
	return minus;
}
void vecTest()
{
	std::vector<int>ivec;
	ivec.reserve(50);
	for(std::vector<int>::size_type ix = 1;ix!=24;++ix)
	{
		ivec.push_back(ix);
	}
	auto beg =ivec.begin();
	auto end =ivec.end();
	ivec.insert(beg+10,888);
	std::cout<<*beg<<std::endl;
}
void vecTest2()
{
	std::vector<int> v = { 0, 1, 2, 3, 4, 5, 6 }; 
	v.reserve(64); 
	std::cout<<v.size()<<std::endl;
	std::cout<<v.capacity()<<std::endl;
	auto begin = v.begin(); 
	v.insert(begin+2,111);
	std::cout<<*begin<<std::endl;
}
int main(int argc,char**argv)
{
	std::string s;
	const char *cp = "Stately,plump Buck";
	s.assign(cp,7);
	std::cout<<s<<std::endl;
	return 0;
}