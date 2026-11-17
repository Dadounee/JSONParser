#ifndef STRUCTS_HPP
# define STRUCTS_HPP

typedef enum e_token_types
{
	undefined,
	string,
	number,
	object,
	array,
	ttrue,
	tfalse,
	tnull
}	t_token_types;

typedef enum e_value_types
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

#endif