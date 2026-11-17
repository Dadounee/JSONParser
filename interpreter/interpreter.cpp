#include "json.hpp"
#include "Token.hpp"
#include <iostream>

t_value	*interpret_array(std::vector<Token *>::iterator &actual, std::vector<Token *>::iterator &end);
t_value	*interpret_object(std::vector<Token *>::iterator &actual, std::vector<Token *>::iterator &end);

t_value	*interpret_string(std::string &value)
{
	std::string	*val = new std::string(value);
	t_value	*new_branch = new t_value;

	new_branch->type = vstring;
	new_branch->value = val;

	return (new_branch);
}

t_value	*interpret_number(std::string &value)
{
	bool 		decimal = (value.find('.') != std::string::npos);
	t_value		*new_branch = new t_value;
	long double	*nb = new long double(strtold(value.c_str(), NULL));

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

t_value	*interpret_ttrue()
{
	bool	*boolean_val = new bool(true);
	t_value	*new_branch = new t_value;

	new_branch->type = vbool;
	new_branch->value = boolean_val;

	return (new_branch);
}

t_value	*interpret_tfalse()
{
	bool	*boolean_val = new bool(false);
	t_value	*new_branch = new t_value;

	new_branch->type = vbool;
	new_branch->value = boolean_val;

	return (new_branch);
}

t_value	*interpret_tnull()
{
	t_value	*new_branch = new t_value;

	new_branch->type = vnull;
	new_branch->value = NULL;

	return (new_branch);
}

t_value	*convertTokens(std::vector<Token *> &tokens)
{
	t_value *tree_root = new t_value;

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

t_value	*interpret_object(std::vector<Token *>::iterator &actual, std::vector<Token *>::iterator &end)
{
	t_value 							*obj_root = new t_value;
	std::string							entry_name = "";
	std::map<std::string, t_value *> 	*obj_values = new std::map<std::string, t_value *>;

	actual++;
	obj_root->value = obj_values;
	for (; actual != end; actual++)
	{
		if (entry_name == "")
		{
			entry_name = *(std::string *)(interpret_string((*actual)->_token))->value;

			if ((*obj_values).find(entry_name) != obj_values->end())
				throw DuplicateObjectKey("Duplicate key in json object found.");
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
				break;
			case array:
				(*obj_values)[entry_name] = interpret_array(actual, end);
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

t_value	*interpret_array(std::vector<Token *>::iterator &actual, std::vector<Token *>::iterator &end)
{
	t_value 				*array_root = new t_value;
	std::vector<t_value * > *arr_values = new std::vector<t_value *>;

	array_root->value = arr_values;

	actual++;
	for (; actual != end; actual++)
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
				break;
			case array:
				arr_values->push_back(interpret_array(actual, end));
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