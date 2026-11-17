#ifndef JSON_HPP
# define JSON_HPP

# include <map>
# include <string>
# include <vector>
# include <limits>

/*

	objects -> std::map<std::string, t_value *>
	array -> std::vector<t_value *>
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
	vbool,
	vchar,
	vshort,
	vint,
	vfloat,
	vlong,
	vdouble,
	vlonglong,
	vlongdouble,
	vnull,
	vmap,
	vvector
}	t_value_types;

typedef struct s_value
{
	t_value_types	type;
	void			*value;
}	t_value;

class DuplicateObjectKey : public std::exception {
	public:
		DuplicateObjectKey(const std::string& message) : _message(message) {};
		virtual const char* what() const throw() { return _message.c_str(); };
		virtual ~DuplicateObjectKey() throw() {};
	private:
		std::string _message;
};

#endif