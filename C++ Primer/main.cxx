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
	unsigned char P2 = 0xff;
	unsigned char i;
	for(i = 0;;++i)
	{
		if(i%8==0)
		{
			i=0;
			P2=0xff;
		}
		P2<<=1;
		//Delay1ms(1000);
		std::cout<<(int)P2<<std::endl;
	}
	

	return 0;
}