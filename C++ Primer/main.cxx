#include<iostream>
#include<vector>
#include<string>
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
int main(int argc,char**argv)
{
	std::vector<int(*)(int,int)>vpf;
	vpf.push_back(&sum);
	vpf.push_back(&minus);
	vpf.push_back(multiply);
	vpf.push_back(division);
	std::cout<<vpf[0](1,1)<<" "
			<<vpf[1](1,1)<<" "
			<<vpf[2](1,1)<<" "
			<<vpf[3](1,1)<<std::endl;
	return 0;
}