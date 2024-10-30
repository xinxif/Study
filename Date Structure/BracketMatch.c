#include"BracketMatch.h"

static bool matched(const char r_bkt, const char l_bkt,stack *stk)
{
	bool success = false;
	//�������ŵ�ASCII�����
	unsigned char sum = r_bkt + l_bkt;
	//�����������ƥ������ŵ�ֵ��ƥ��ɹ�
	switch (sum)
	{
	case l_parentheses + r_parentheses:;
	case l_square_brackets + r_square_brackets:
	case l_curly_braces + r_curly_braces:
		pop(*stk);//ƥ��ɹ�����ջ��Ԫ��
		success = true;
		break;
	}
	return success;
}
size_t bracket_match(const char* brackets, size_t lenght)
{
	stack stk = init();
	enum bracket bkt;
	char top_chr;//ջ��Ԫ��
	size_t i;	//�����±�,���û��ƥ��ɹ����ش������ŵ��±�
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
		puts("ƥ��ɹ�");
	}
	else
	{
		puts("ƥ��ʧ��");
	}
#endif // !__BRACKET_MATCH_NDEBUG__

	destory_stack(stk);
	return loop ? 0U : i;//�������Ӧ����ʵ���±�+1��λ��
}