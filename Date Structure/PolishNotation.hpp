#pragma once
#include<string>
#include<stack>
#include<cstdlib>
#include<map>
#ifndef __POLISH_NOTAION_NDEBUG__
#include<iostream>
using std::cout;
using std::endl;
using std::cerr;
#endif // !__POLISH_NOTAION_NDEBUG__

enum operational_symbol :char
{
	plus			= 43U,
	subtraction		= 45U,
	multiplication	= 42U,
	division		= 47U,
	l_parenthesis	= 40U,
	r_parenthesis	= 41U
};
enum digit :char
{
	zero	= 48,
	one		= 49,
	two		= 50,
	three	= 51,
	four	= 52,
	five	= 53,
	six		= 54,
	seven	= 55,
	eight	= 56,
	nine	= 57
};
std::string convert_to_PN(const std::string& infix);
double calculate_RPN(const std::string& RPN);