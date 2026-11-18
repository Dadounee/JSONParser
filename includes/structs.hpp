#ifndef STRUCTS_HPP
# define STRUCTS_HPP

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

typedef struct s_value
{
	void			*value;
	t_value_types	type;
}	t_value;

#endif