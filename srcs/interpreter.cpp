#include "Json.hpp"
#include "Token.hpp"
#include <iostream>

JsonData	*JSON_resources_internal(std::vector<Token *>::iterator &begin, std::vector<Token *>::iterator &end);

JsonData	*interpret_number(std::string &value)
{
	bool 			decimal = (value.find('.') != std::string::npos);
	JsonData		*new_branch = new JsonData;
	long double		*nb = new (long double)(strtold(value.c_str(), NULL));

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

JsonData	*interpret_string(std::string &value) { return (new JsonData(new std::string(value), vstring)); }

JsonData	*interpret_ttrue() { return (new JsonData(new bool(true), vbool)); }

JsonData	*interpret_tfalse() { return (new JsonData(new bool(false), vbool)); }

JsonData	*interpret_tnull() { return (new JsonData(NULL, vnull)); }

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
		if ((*actual)->_type == array || (*actual)->_type == object)
		{
			(*obj_values)[entry_name] = JSON_resources_internal(actual, end);
			actual--;
		}
		else
			(*obj_values)[entry_name] = JSON_resources_internal(actual, end);
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
		JsonData	*tmp;
		if ((*actual)->_type == array || (*actual)->_type == object)
		{
			tmp = JSON_resources_internal(actual, end);
			actual--;
		}
		else
			tmp = JSON_resources_internal(actual, end);
		if (tmp != NULL)
			arr_values->push_back(tmp);
		if (actual == end)
			break;
	}

	return (array_root);
}

JsonData	*JSON_resources_internal(std::vector<Token *>::iterator &begin, std::vector<Token *>::iterator &end)
{
	switch ((*begin)->_type)
	{
		case string:
			return (interpret_string((*begin)->_token));
		case number:
			return (interpret_number((*begin)->_token));
		case object:
			return (interpret_object(begin, end));
		case array:
			return (interpret_array(begin, end));
		case ttrue:
			return (interpret_ttrue());
		case tfalse:
			return (interpret_tfalse());
		case tnull:
			return (interpret_tnull());
		default:
			return (NULL);
	}
}

JsonData	*Json::JSON_resources(std::vector<Token *> &tokens)
{
	std::vector<Token *>::iterator	begin = tokens.begin();
	std::vector<Token *>::iterator	end = tokens.end();
	return (JSON_resources_internal(begin, end));
}