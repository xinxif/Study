#include"PolishNotation.hpp"
static void process_op_sym(std::stack<char>& dis_op_sym, std::string& RPN,bool including_plus_minus)
{
	char top_sym;
	bool loop_control = true;
	while (loop_control&&!dis_op_sym.empty())
	{
		top_sym = dis_op_sym.top();//查看栈顶运算符
		switch (top_sym)
		{
		case plus:
		case subtraction:
			if (!including_plus_minus)//在处理*/的时候碰到了级别底的+-，循环结束
			{
				loop_control = false;
				break;
			}
		case multiplication:
		case division:
			RPN += top_sym;
			dis_op_sym.pop();//只有+-*/弹出
			break;
		default://碰到了左括号
			loop_control = false;
			break;
		}
	}
}
template <typename ty>
static ty pls(const ty val1, const ty val2)
{
	return val1 + val2;
}
template<typename ty>
static ty minus(const ty val1, const ty val2)
{
	return val1 - val2;
}
template<typename ty>
static ty multiply(const ty val1, const ty val2)
{
	return val1 * val2;
}
template<typename ty>
static ty divi(const ty val1, const ty val2)
{
	return val1 / val2;
}

std::string convert_to_PN(const std::string& infix)
{
	/*
	- 遇到操作数。直接加入后缀表达式。
	- 遇到界限符。`(`直接入栈；遇到`)`则依次弹出栈内运算符并加入后缀表达式，直到弹出`(`为止。注意:`(`不加入后缀表达式。
	- 遇到运算符。依次弹出栈中**优先级**高于或等于当前运算符的所有运算符，并加入后缀表达式，若碰到`(`或栈空则停止。之后再把当前运算符入栈。
	*/
#ifndef __POLISH_NOTAION_NDEBUG__
	std::string test1("A*(B+C)/(D-E)+F");
#endif // !__POLISH_NOTAION_NDEBUG__

	std::stack<char> dis_op_sym;
	std::string RPN;//逆波兰表达式
	char ch;//每一个中缀表达式的字符
	char op_sym;//栈顶的运算符

	for (size_t i = 0U; i < infix.size(); ++i)
	{
		ch = infix[i];
		switch (ch)
		{
		case plus:
		case subtraction:
			if (dis_op_sym.empty())
			{
				dis_op_sym.push(ch);//空栈运算符入栈
				continue;			//进行下一次处理
			}
			process_op_sym(dis_op_sym, RPN,true); //弹出栈中高于或等于当前运算符的所有运算符，包含+-运算符
			dis_op_sym.push(ch);//再把当前运算符入栈
			break;
		case multiplication:
		case division:
			if (dis_op_sym.empty())
			{
				dis_op_sym.push(ch);
				continue;
			}
			process_op_sym(dis_op_sym, RPN,false);
			dis_op_sym.push(ch);
			break;
		case l_parenthesis://(左阔号直接入栈
			dis_op_sym.push(ch);
			break;
		case r_parenthesis:
			//栈顶运算符不等于(
			while ((op_sym = dis_op_sym.top()) != l_parenthesis)
			{
				RPN += op_sym;
				dis_op_sym.pop();
			}
			dis_op_sym.pop();//弹出左括号
			break;
		default:
			RPN += ch;
			break;
		}
	}

	while (!dis_op_sym.empty())//栈中还有运算符直接放在逆波兰表达式后
	{
		RPN += dis_op_sym.top();
		dis_op_sym.pop();
	}
#ifndef __POLISH_NOTAION_NDEBUG__
	cout << RPN << endl;
#endif // !__POLISH_NOTAION_NDEBUG__
	return RPN;
}

//数字要用空格分割
double calculate_RPN(const std::string& RPN)
{
	typedef double(*func)(const double, const double);
	std::map<char, func> operations;
	operations['+'] = pls<double>;
	operations['-'] = minus<double>;
	operations['*'] = multiply<double>;
	operations['/'] = divi<double>;


	char ch;//读逆波兰表达式的每一个字符
	std::string str_number;//字符串数字
	double dbl_number;//实际的数字
	std::stack<double> stk;//存放数字
	double l_num, r_num;
	
	for (size_t i = 0; i < RPN.size(); ++i)
	{
		ch = RPN[i];
		switch (ch)
		{
		case zero:
		case one:
		case two:
		case three:
		case four:
		case five:
		case six:
		case seven:
		case eight:
		case nine:
			str_number += ch;
			break;
		case plus:
		case subtraction:
		case multiplication:
		case division:
			//数字和运算符没有被正常分割
			if (str_number.size())
			{
				dbl_number = std::stod(str_number);
				stk.push(dbl_number);

				//清空数据
				str_number.clear();
			}

			r_num = stk.top(); stk.pop();
			l_num = stk.top(); stk.pop();
			
			stk.push(operations[ch](l_num, r_num));
			break;
		default://读到了空格认为一个数字完成
			if (str_number.empty())continue;

			dbl_number = std::stod(str_number);
			stk.push(dbl_number);

			//清空数据
			str_number.clear();
			break;
		}
	}
	return stk.top();
}