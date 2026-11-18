#include "Json.hpp"
#include "Token.hpp"
#include <iostream>

JsonData	*interpret_array(std::vector<Token *>::iterator &actual, std::vector<Token *>::iterator &end);
JsonData	*interpret_object(std::vector<Token *>::iterator &actual, std::vector<Token *>::iterator &end);

JsonData	*interpret_string(std::string &value)
{
	std::string	*val = new std::string(value);
	JsonData	*new_branch = new JsonData;

	new_branch->type = vstring;
	new_branch->value = val;

	return (new_branch);
}

JsonData	*interpret_number(std::string &value)
{
	bool 		decimal = (value.find('.') != std::string::npos);
	JsonData		*new_branch = new JsonData;
	long double	*nb = new (long double)(strtold(value.c_str(), NULL));

	new_branch->value = nb;

	if (decimal)
	{
		if (*nb > std::numeric_limits<float>::min() && *nb < std::numeric_limits<float>::max())
			new_branch->type = vfloat;
		else if (*nb > std::numeric_limits<double>::min() && *nb < std::numeric_limits<double>::max())
			new_branch->type = vdouble;
		else
			new_branch->type = vlongdouble;
	}
	else
	{
		if (*nb > std::numeric_limits<char>::min() && *nb < std::numeric_limits<char>::max())
			new_branch->type = vchar;
		if (*nb > std::numeric_limits<short>::min() && *nb < std::numeric_limits<short>::max())
			new_branch->type = vshort;
		if (*nb > std::numeric_limits<int>::min() && *nb < std::numeric_limits<int>::max())
			new_branch->type = vint;
		if (*nb > std::numeric_limits<long>::min() && *nb < std::numeric_limits<long>::max())
			new_branch->type = vlong;
		if (*nb > std::numeric_limits<long long>::min() && *nb < std::numeric_limits<long long>::max())
			new_branch->type = vlonglong;
		else
			new_branch->type = vlongdouble;

	}
	return (new_branch);
}

JsonData	*interpret_ttrue() { return (new JsonData(new bool(true), vbool)); }

JsonData	*interpret_tfalse() { return (new JsonData(new bool(false), vbool)); }

JsonData	*interpret_tnull() { return (new JsonData(NULL, vnull)); }

JsonData	*Json::JSON_resources(std::vector<Token *> &tokens)
{
	JsonData *tree_root = NULL;

	std::vector<Token *>::iterator begin = tokens.begin();
	std::vector<Token *>::iterator end = tokens.end();

	switch (tokens[0]->_type)
	{
		case string:
			tree_root = interpret_string(tokens[0]->_token);
			break;
		case number:
			tree_root = interpret_number(tokens[0]->_token);
			break;
		case object:
			tree_root = interpret_object(begin, end);
			break;
		case array:
			tree_root = interpret_array(begin, end);
			break;
		case ttrue:
			tree_root = interpret_ttrue();
			break;
		case tfalse:
			tree_root = interpret_tfalse();
			break;
		case tnull:
			tree_root = interpret_tnull();
			break;
		default:
			break;
	}

	return (tree_root);
}

JsonData	*interpret_object(std::vector<Token *>::iterator &actual, std::vector<Token *>::iterator &end)
{
	std::string							entry_name = "";
	std::map<std::string, JsonData *> 	*obj_values = new std::map<std::string, JsonData *>;
	JsonData 							*obj_root = new JsonData(obj_values, vmap);
	Token								*parent = *actual;

	actual++;
	for (; actual != end && (((*actual)->_parent == parent && entry_name == "") || entry_name != ""); actual++)
	{
		if (entry_name == "")
		{
			entry_name = (*actual)->_token;

			if ((*obj_values).find(entry_name) != obj_values->end())
				throw Json::DuplicateObjectKey();
			continue;
		}
		switch ((*actual)->_type)
		{
			case string:
				(*obj_values)[entry_name] = interpret_string((*actual)->_token);
				break;
			case number:
				(*obj_values)[entry_name] = interpret_number((*actual)->_token);
				break;
			case object:
				(*obj_values)[entry_name] = interpret_object(actual, end);
				actual--;
				break;
			case array:
				(*obj_values)[entry_name] = interpret_array(actual, end);
				actual--;
				break;
			case ttrue:
				(*obj_values)[entry_name] = interpret_ttrue();
				break;
			case tfalse:
				(*obj_values)[entry_name] = interpret_tfalse();
				break;
			case tnull:
				(*obj_values)[entry_name] = interpret_tnull();
				break;
			default:
				break;
		}
		entry_name = "";
		if (actual == end)
			break;
	}

	return (obj_root);
}

JsonData	*interpret_array(std::vector<Token *>::iterator &actual, std::vector<Token *>::iterator &end)
{
	JsonData 				*array_root = new JsonData;
	std::vector<JsonData * > *arr_values = new std::vector<JsonData *>;
	Token					*parent = *actual;

	array_root->type = vvector;
	array_root->value = arr_values;

	actual++;
	for (; actual != end && (*actual)->_parent == parent; actual++)
	{
		switch ((*actual)->_type)
		{
			case string:
				arr_values->push_back(interpret_string((*actual)->_token));
				break;
			case number:
				arr_values->push_back(interpret_number((*actual)->_token));
				break;
			case object:
				arr_values->push_back(interpret_object(actual, end));
				actual--;
				break;
			case array:
				arr_values->push_back(interpret_array(actual, end));
				actual--;
				break;
			case ttrue:
				arr_values->push_back(interpret_ttrue());
				break;
			case tfalse:
				arr_values->push_back(interpret_tfalse());
				break;
			case tnull:
				arr_values->push_back(interpret_tnull());
				break;
			default:
				break;
		}
		if (actual == end)
			break;
	}

	return (array_root);
}