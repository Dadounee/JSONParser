#include "json.hpp"
#include "Token.hpp"
#include <iostream>

void	displayJson(t_value &json, int ac_depth);

void	displayArr(t_value &json, int ac_depth)
{
	std::vector<t_value *>	vals = *(std::vector<t_value *> *)json.value;

	for (int i = 0; i < ac_depth-1; i++)
		std::cout << "\t";
	std::cout << "[\n";

	for (size_t i = 0; i < vals.size(); i++)
	{
		for (int i = 0; i < ac_depth; i++)
			std::cout << "\t";
		displayJson(*vals[i], ac_depth);
		if (i+1 != vals.size())
			std::cout << ",";
		std::cout << "\n";
	}
	for (int i = 0; i < ac_depth; i++)
		std::cout << "\t";
	std::cout << "]";
}

void	displayObj(t_value &json, int ac_depth)
{
	std::map<std::string, t_value *>	vals = *(std::map<std::string, t_value *> *)json.value;

	for (int i = 0; i < ac_depth-1; i++)
		std::cout << "\t";
	std::cout << "{\n";

	for (std::map<std::string, t_value *>::iterator it= vals.begin(); it != vals.end(); it++)
	{
		for (int i = 0; i < ac_depth; i++)
			std::cout << "\t";
		std::cout << "\"" << it->first << "\"";
		std::cout << ":";
		displayJson(*it->second, 0);
		if (it++ != vals.end())
		{
			std::cout << ",";
			it--;
		}
		std::cout << "\n";
	}
	for (int i = 0; i < ac_depth; i++)
		std::cout << "\t";
	std::cout << "}";
}

void	displayJson(t_value &json, int ac_depth)
{
	for (int i = 0; i < ac_depth; i++)
		std::cout << "\t";
	switch (json.type)
	{
	case vstring:
		std::cout << "\"" << *(std::string *)json.value << "\"";
		break;
	case vnull:
		std::cout << "null";
		break;
	case vbool:
		std::cout << (*(bool *)json.value ? "true" : "false");
		break;
	case vmap:
		displayObj(json, ac_depth + 1);
		break;
	case vvector:
		displayArr(json, ac_depth + 1);
		break;
	default:
		std::cout << *(long double *)json.value;
		break;
	}
}