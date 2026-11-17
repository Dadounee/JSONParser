#ifndef JSON_HPP
# define JSON_HPP

# include <string>
# include <vector>
# include "Token.hpp"

/*

	objects -> std::map<std::string, t_value>
	array -> std::vector<t_value>
	else
	thing -> t_value
*/

int	tokenizer(std::string& input, std::vector<Token *>& output);

#endif