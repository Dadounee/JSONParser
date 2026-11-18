#include "Json.hpp"

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