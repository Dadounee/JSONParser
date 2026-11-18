#ifndef STRUCT_HPP
# define STRUCT_HPP

typedef enum e_value_types
{
	vstring,
	vnull,
	vmap,
	vvector,
	vbool,
	vchar,
	vshort,
	vint,
	vfloat,
	vlong,
	vdouble,
	vlonglong,
	vlongdouble
}	t_value_types;

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

typedef struct s_value
{
	void			*value;
	t_value_types	type;
}	t_value;

#endif