#ifndef JSON_HPP
# define JSON_HPP

# include <string>
# include <vector>

typedef enum e_token_types : uint8_t
{
	undefined,
	string,
	number,
	ttrue,
	tfalse,
	null,
	object,
	array,
	colon,
	comma
}	t_token_types;

typedef struct s_token
{
	std::string		token;
	t_token_types	type;
	t_token 		*parent;
}	t_token;

#endif