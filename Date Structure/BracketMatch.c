#include"BracketMatch.h"

static bool matched(const char r_bkt, const char l_bkt,stack *stk)
{
	bool success = false;
	//两个括号的ASCII码相加
	unsigned char sum = r_bkt + l_bkt;
	//结果等于两个匹配的括号的值，匹配成功
	switch (sum)
	{
	case l_parentheses + r_parentheses:;
	case l_square_brackets + r_square_brackets:
	case l_curly_braces + r_curly_braces:
		pop(*stk);//匹配成功弹出栈顶元素
		success = true;
		break;
	}
	return success;
}
size_t bracket_match(const char* brackets, size_t lenght)
{
	stack stk = init();
	enum bracket bkt;
	char top_chr;//栈顶元素
	size_t i;	//数组下标,如果没有匹配成功返回错误括号的下标
	bool loop = true;

	for (i = 0; i < lenght && loop; ++i)
	{
		bkt = brackets[i];
		switch (bkt)
		{
		case l_parentheses:
		case l_square_brackets:
		case l_curly_braces:
			push(stk, bkt);
			break;
		case r_parentheses:
		case r_square_brackets:
		case r_curly_braces:
			top_chr = top(stk) ? *top(stk) : 0X0;
			loop = matched(top_chr, bkt, &stk);
			break;
		default:
			break;
		}
	}
#ifndef __BRACKET_MATCH_NDEBUG__
	if (empty(stk))
	{
		puts("匹配成功");
	}
	else
	{
		puts("匹配失败");
	}
#endif // !__BRACKET_MATCH_NDEBUG__

	destory_stack(stk);
	return loop ? 0U : i;//括号相对应返回实际下标+1的位置
}