#ifndef JSON_HPP
# define JSON_HPP

# include <string>
# include <vector>

/*

	objects -> std::map<std::string, t_value>
	array -> std::vector<t_value>
	else
	thing -> t_value
*/

typedef enum e_token_types : uint8_t
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

typedef enum e_value_types : uint8_t
{
	vstring,
	vint,
	vdouble,
	vmap,
	vvector
}	t_value_types;

typedef struct s_value
{
	t_value_types	type;
	void			*value;
}	t_value;

typedef struct s_token
{
	std::string		token;
	t_token_types	type;
	t_token 		*parent;
}	t_token;

#endif