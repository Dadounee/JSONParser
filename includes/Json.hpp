#ifndef JSON_HPP
# define JSON_HPP

# include "Token.hpp"

# include <map>
# include <string>
# include <vector>
# include <limits>
# include <cstdlib>

typedef enum e_value_types
{
	vnull,
	vstring,
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

class JsonData
{
	public:
		void			*value;
		t_value_types	type;
		JsonData();
		JsonData(void *val, t_value_types typ);
		JsonData(const JsonData& other);
		~JsonData();
		JsonData&		operator=(const JsonData& other);
};

class Json
{
	private:
		Json();
		Json(const Json& other);
		static int		tokenizer(std::string& input, std::vector<Token *>& output);
		static JsonData	*JSON_resources(std::vector<Token *> &tokens);
		static void		displayArr(JsonData &json, int ac_depth);
		static void		displayObj(JsonData &json, int ac_depth);
		static void		displayJson(JsonData &json, int ac_depth, bool in_obj);
	public:
		class DuplicateObjectKey : public std::exception {
			public: virtual const char* what() const throw() { return "Duplicate key in json object found."; };
		};
		virtual Json&	operator=(const Json& other) = 0;
		virtual ~Json() = 0;

		static JsonData		*convert(std::string& to_convert);
		// static std::string	*convert(JsonData& to_convert);
		static void			display(JsonData& to_display);
		static bool			validate(std::string& to_validate);
};

#endif