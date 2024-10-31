#include"PolishNotation.hpp"
static void process_op_sym(std::stack<char>& dis_op_sym, std::string& RPN,bool including_plus_minus)
{
	char top_sym;
	bool loop_control = true;
	while (loop_control&&!dis_op_sym.empty())
	{
		top_sym = dis_op_sym.top();//�鿴ջ�������
		switch (top_sym)
		{
		case plus:
		case subtraction:
			if (!including_plus_minus)//�ڴ���*/��ʱ�������˼���׵�+-��ѭ������
			{
				loop_control = false;
				break;
			}
		case multiplication:
		case division:
			RPN += top_sym;
			dis_op_sym.pop();//ֻ��+-*/����
			break;
		default://������������
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
	- ������������ֱ�Ӽ����׺���ʽ��
	- �������޷���`(`ֱ����ջ������`)`�����ε���ջ��������������׺���ʽ��ֱ������`(`Ϊֹ��ע��:`(`�������׺���ʽ��
	- ��������������ε���ջ��**���ȼ�**���ڻ���ڵ�ǰ�������������������������׺���ʽ��������`(`��ջ����ֹͣ��֮���ٰѵ�ǰ�������ջ��
	*/
#ifndef __POLISH_NOTAION_NDEBUG__
	std::string test1("A*(B+C)/(D-E)+F");
#endif // !__POLISH_NOTAION_NDEBUG__

	std::stack<char> dis_op_sym;
	std::string RPN;//�沨�����ʽ
	char ch;//ÿһ����׺���ʽ���ַ�
	char op_sym;//ջ���������

	for (size_t i = 0U; i < infix.size(); ++i)
	{
		ch = infix[i];
		switch (ch)
		{
		case plus:
		case subtraction:
			if (dis_op_sym.empty())
			{
				dis_op_sym.push(ch);//��ջ�������ջ
				continue;			//������һ�δ���
			}
			process_op_sym(dis_op_sym, RPN,true); //����ջ�и��ڻ���ڵ�ǰ����������������������+-�����
			dis_op_sym.push(ch);//�ٰѵ�ǰ�������ջ
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
		case l_parenthesis://(������ֱ����ջ
			dis_op_sym.push(ch);
			break;
		case r_parenthesis:
			//ջ�������������(
			while ((op_sym = dis_op_sym.top()) != l_parenthesis)
			{
				RPN += op_sym;
				dis_op_sym.pop();
			}
			dis_op_sym.pop();//����������
			break;
		default:
			RPN += ch;
			break;
		}
	}

	while (!dis_op_sym.empty())//ջ�л��������ֱ�ӷ����沨�����ʽ��
	{
		RPN += dis_op_sym.top();
		dis_op_sym.pop();
	}
#ifndef __POLISH_NOTAION_NDEBUG__
	cout << RPN << endl;
#endif // !__POLISH_NOTAION_NDEBUG__
	return RPN;
}

//����Ҫ�ÿո�ָ�
double calculate_RPN(const std::string& RPN)
{
	typedef double(*func)(const double, const double);
	std::map<char, func> operations;
	operations['+'] = pls<double>;
	operations['-'] = minus<double>;
	operations['*'] = multiply<double>;
	operations['/'] = divi<double>;


	char ch;//���沨�����ʽ��ÿһ���ַ�
	std::string str_number;//�ַ�������
	double dbl_number;//ʵ�ʵ�����
	std::stack<double> stk;//�������
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
			//���ֺ������û�б������ָ�
			if (str_number.size())
			{
				dbl_number = std::stod(str_number);
				stk.push(dbl_number);

				//�������
				str_number.clear();
			}

			r_num = stk.top(); stk.pop();
			l_num = stk.top(); stk.pop();
			
			stk.push(operations[ch](l_num, r_num));
			break;
		default://�����˿ո���Ϊһ���������
			if (str_number.empty())continue;

			dbl_number = std::stod(str_number);
			stk.push(dbl_number);

			//�������
			str_number.clear();
			break;
		}
	}
	return stk.top();
}