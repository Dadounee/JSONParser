#ifndef JSON_HPP
# define JSON_HPP

# include <string>
# include <vector>

typedef enum e_token_types : uint8_t
{
	string,
	number,
	ttrue,
	tfalse,
	null,
	obj_start,
	obj_end,
	arr_start,
	arr_end,
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