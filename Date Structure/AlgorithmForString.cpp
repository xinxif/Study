#include"AlgorithmForString.hpp"
namespace strfnd
{
	std::pair<std::string::size_type, std::string::size_type>
		find(const std::string& main, const std::string& patt)
	{

		std::pair<std::string::size_type, std::string::size_type> bae(0, 0);
		std::string::size_type mi_idx(0), patt_idx(0);

		while (mi_idx < main.size() && patt_idx < patt.size())
		{
			if (main[mi_idx] == patt[patt_idx])
			{
				++mi_idx, ++patt_idx;
			}
			else
			{
				mi_idx = mi_idx - patt_idx + 1;
				patt_idx = 0;
			}

		}
		if (mi_idx != main.size())
		{
			bae.first = mi_idx - patt.size();
			bae.second = mi_idx;
		}
		return bae;

	}

}
