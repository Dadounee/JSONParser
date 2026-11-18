#ifndef TOKEN_HPP
# define TOKEN_HPP

# include "Json.hpp"
# include "structs.hpp"
# include <string>
# include <vector>

typedef enum e_token_types
{
	undefined,
	string,
	number,
	object,
	array,
	ttrue,
	tfalse,
	tnull,
	colon,
	comma
}	t_token_types;

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