#include"BracketMatch.h"

static bool matched(const char r_bkt, const char l_bkt)
{
	bool success;
	//�������ŵ�ASCII�����
	unsigned char sum = r_bkt + l_bkt;
	//�����������ƥ������ŵ�ֵ��ƥ��ɹ�
	switch (sum)
	{
	case l_parentheses + r_parentheses:
		success = true;
		break;
	case l_square_brackets + r_square_brackets:
		success = true;
		break;
	case l_curly_braces + r_curly_braces:
		success = true;
		break;
	default:
		success = false;
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
			top_chr = *top(stk);
			if (matched(top_chr, bkt))
			{
				pop(stk);//ƥ��ɹ�����ջ��Ԫ��
			}
			else
			{
				loop = false;
			}
			break;
		default:
			break;
		}
	}
	//printf("%c", *top(stk));
	if (empty(stk))
	{
		puts("ƥ��ɹ�");
		i = 1u;
	}
	else
	{
		puts("ʧ��");
	}
	destory_stack(stk);
	return --i;
}