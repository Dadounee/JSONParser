#ifndef JSON_HPP
# define JSON_HPP

# include "Token.hpp"
# include "structs.hpp"

# include <map>
# include <string>
# include <vector>
# include <limits>
# include <cstdlib>


class DuplicateObjectKey : public std::exception {
	public:
		DuplicateObjectKey(const std::string& message) : _message(message) {};
		virtual const char* what() const throw() { return _message.c_str(); };
		virtual ~DuplicateObjectKey() throw() {};
	private:
		std::string _message;
};

int	tokenizer(std::string& input, std::vector<Token *>& output);
void	displayJson(t_value &json, int ac_depth);

#endif