#ifndef __ALGORITHM_FOR_STRING__
#define __ALGORITHM_FOR_STRING__
#include<string>
#include<utility>
#ifndef __ALGORITHM_FOR_STRING_NDEBUG__
#include<iostream>
#endif // !__ALGORITHM_FOR_STRING_NDEBUG__

namespace strfnd
{
	std::pair<std::string::size_type, std::string::size_type>
		find(const std::string& main, const std::string& patt);
	
}


#endif // !__ALGORITHM_FOR_STRING__
