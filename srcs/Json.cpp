#include "Json.hpp"

JsonData::JsonData() : value(NULL), type(vnull)
{

}

JsonData::JsonData(const JsonData& other): value(other.value), type(other.type)
{

}
JsonData::JsonData(void *val, t_value_types typ): value(val), type(typ)
{

}

JsonData::~JsonData()
{
	switch (type)
	{
		case vnull:
			break;
		case vstring:
			delete (std::string *)value;
			break;
		case vmap:
			for (std::map<std::string, JsonData *>::iterator it = ((std::map<std::string, JsonData *> *)value)->begin(); it!= ((std::map<std::string, JsonData *> *)value)->end(); it++)
				delete it->second;
			delete (std::map<std::string, JsonData *> *)value;
			break;
		case vvector:
			for (std::vector<JsonData *>::iterator it = ((std::vector<JsonData *> *)value)->begin(); it!= ((std::vector<JsonData *> *)value)->end(); it++)
				delete *it;
			delete (std::vector<JsonData *> *)value;
			break;
		case vbool:
			delete (bool *)value;
			break;
		case vchar:
			delete (char *)value;
			break;
		case vshort:
			delete (short *)value;
			break;
		case vint:
			delete (int *)value;
			break;
		case vfloat:
			delete (float *)value;
			break;
		case vlong:
			delete (long *)value;
			break;
		case vdouble:
			delete (double *)value;
			break;
		case vlonglong:
			delete (long long *)value;
			break;
		case vlongdouble:
			delete (long double *)value;
			break;
		default:
			break;
	}
}

JsonData&		JsonData::operator=(const JsonData& other)
{
	value = other.value;
	type = other.type;
	return (*this);
}


JsonData	*Json::convert(std::string& to_convert)
{
	std::vector<Token *>	res;
	int code = tokenizer(to_convert, res);
	if (code)
		return (NULL);
	JsonData	*ret = JSON_resources(res);
	for (size_t i = 0; i < res.size(); i++)
		delete res[i];
	return (ret);
}

void		Json::display(JsonData& to_display)
{
	displayJson(to_display, 0, false);
}

bool		Json::validate(std::string& to_validate)
{
	std::vector<Token *>	res;
	int code = tokenizer(to_validate, res);
	for (size_t i = 0; i < res.size(); i++)
		delete res[i];
	return (code);
}