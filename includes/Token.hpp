#ifndef TOKEN_HPP
# define TOKEN_HPP

# include <string>
# include "structs.hpp"

class Token
{
public:
	std::string		_token;
	t_token_types	_type;
	Token 			*_parent;

	Token(std::string token, t_token_types type, Token *parent);
	Token(const Token& other);
	Token&	operator=(const Token& other);
	~Token();
};

#endif