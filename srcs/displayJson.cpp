#include "Json.hpp"
#include "Token.hpp"
#include <iostream>

void	Json::displayArr(JsonData &json, int ac_depth)
{
	std::vector<JsonData *>	vals = *(std::vector<JsonData *> *)json.value;

	for (size_t i = 0; i < vals.size(); i++)
	{
		for (int i = 0; i < ac_depth; i++)
			std::cout << "\t";
		Json::displayJson(*vals[i], ac_depth, true);
		if (i+1 != vals.size())
			std::cout << ",";
		std::cout << "\n";
	}
	for (int i = 0; i < ac_depth-1; i++)
		std::cout << "\t";
	std::cout << "]";
}

void	Json::displayObj(JsonData &json, int ac_depth)
{
	std::map<std::string, JsonData *>	vals = *(std::map<std::string, JsonData *> *)json.value;

	for (std::map<std::string, JsonData *>::iterator it= vals.begin(); it != vals.end(); it++)
	{
		for (int i = 0; i < ac_depth; i++)
			std::cout << "\t";
		std::cout << "\"" << it->first << "\"";
		std::cout << ":";
		Json::displayJson(*it->second, ac_depth, true);
		if (it != --vals.end())
			std::cout << ",";
		std::cout << "\n";
	}
	for (int i = 0; i < ac_depth-1; i++)
		std::cout << "\t";
	std::cout << "}";
}

void	Json::displayJson(JsonData &json, int ac_depth, bool in_obj)
{
	if (!in_obj)
	{
		for (int i = 0; i < ac_depth; i++)
			std::cout << "\t";
	}
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
		std::cout << "{\n";
		displayObj(json, ac_depth + 1);
		break;
	case vvector:
		std::cout << "[\n";
		displayArr(json, ac_depth + 1);
		break;
	default:
		std::cout << *(long double *)json.value;
		break;
	}
	if (ac_depth == 0)
		std::cout << std::endl;
}