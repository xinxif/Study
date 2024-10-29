#ifndef __BRACKET_MATCH__
#define __BRACKET_MATCH__
#include"Stack.h"
#ifndef __BRACKET_MATCH_NDEBUG__
#include<stdio.h>
#endif // !__BRACKET_MATCH_NDEBUG__

enum bracket
{
    l_parentheses = 40U,
    r_parentheses = 41U,
    l_square_brackets = 91U,
    r_square_brackets = 93U,
    l_curly_braces = 123U,
    r_curly_braces = 125U

};
size_t bracket_match(const char* brackets, size_t lenght);



#endif // !__BRACKET_MATCH__

