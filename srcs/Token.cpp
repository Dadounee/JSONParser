#include "Token.hpp"

void	Token::Token(std::string token, t_token_types type, Token *parent): _token(token), _type(type), _parent(parent) {}

void	Token::Token(const Token& other): _token(other._token), _type(other._type), _parent(other._parent) {}

Token&	Token::operator=(const Token& other)
{
	if (this != &other)
	{
		_token = other._token;
		_type = other._type;
		_parent = other._parent;
	}
	return (*this);
}

void	Token::~Token() {}