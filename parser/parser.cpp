#include "Json.hpp"
#include "Token.hpp"
#include <cctype>

static bool	is_values_parent_valid(Token *curr_parent, bool is_str)
{
	if (curr_parent)
	{
		if (is_str && curr_parent->_type != array && curr_parent->_type != string && curr_parent->_type != object)
			return (false);
		if (!is_str && curr_parent->_type != array && curr_parent->_type != string)
			return (false);
		if (curr_parent->_type == string && curr_parent->_parent && curr_parent->_parent->_type == string)
			return (false);
	}
	return (true);
}

static bool	check_bool(std::string& input, std::string::iterator& it, std::vector<Token *>& output, Token *&curr_parent)
{
	Token	*new_token;
	if ((std::distance(it, input.end()) >= 5 && input.compare(it - input.begin(), 4, "true") == 0) ||
	(std::distance(it, input.end()) >= 6 && input.compare(it - input.begin(), 5, "false") == 0) ||
	(std::distance(it, input.end()) >= 5 && input.compare(it - input.begin(), 4, "null") == 0))
	{
		if (!is_values_parent_valid(curr_parent, false))
			return (true);
		if (input.compare(it - input.begin(), 4, "true") == 0)
			new_token = new Token("", ttrue, curr_parent);
		else if (input.compare(it - input.begin(), 5, "false") == 0)
		{
			new_token = new Token("", tfalse, curr_parent);
			it++;
		}
		else
			new_token = new Token("", tnull, curr_parent);
		output.push_back(new_token);
		it += 3;
		if (curr_parent && curr_parent->_type == string)
			curr_parent = curr_parent->_parent;
	}
	return (false);
}

static bool	do_string(std::string& input, std::string::iterator& it, std::vector<Token *>& output, Token *&curr_parent)
{
	std::string::iterator	start = it;
	bool					check_backslash = false;
	while (it != input.end() && *it != '"')
	{
		if (check_backslash)
		{
			switch (*it)
			{
				case 'u':
					if (std::distance(it, input.end()) < 6)
						return (true);
					if (!isxdigit((*it + 1)) || !isxdigit((*it + 2)) || !isxdigit((*it + 3)) || !isxdigit((*it + 4)))
						return (true);
					std::advance(it, 4);
					check_backslash = false;
					break ;
				case '"': case '\\': case '/': case 'b': case 'f': case 'n': case 'r': case 't':
					check_backslash = false;
					break ;
				default:
					return (true);
			}
		}
		else
		{
			if (!isprint(*it))
				return (true);
			else if (*it == '\\')
				check_backslash = true;
		}
		it++;
	}
	if (it == input.end())
		return (true);
	Token	*new_token = new Token(input.substr(start - input.begin(), it - start), string, curr_parent);
	output.push_back(new_token);
	if (!curr_parent || (curr_parent->_type != string && curr_parent->_type != array))
		curr_parent = new_token;
	else if (curr_parent->_type == string)
		curr_parent = curr_parent->_parent;
	return (false);
}

static bool	do_number(std::string& input, std::string::iterator& it, std::vector<Token *>& output, Token *&curr_parent)
{
	int						phase = 0;
	bool					from_zero = false;
	std::string::iterator	start = it;
	if (*it == '-')
		it++;
	while (it != input.end() && !(isspace(*it) && *it != '\v') && *it != ']' && *it != ',' && *it != '}')
	{
		if (phase == 0)
		{
			if (*it == 0)
			{
				phase = 2;
				from_zero = true;
			}
			else if (!isdigit(*it))
				return (true);
			else
				phase = 1;
		}
		else if (phase == 1)
		{
			if (*it == '.')
			{
				phase = 2;
				continue ;
			}
			else if (*it == 'e' || *it == 'E')
			{
				phase = 4;
				continue ;
			}
			else if (!isdigit(*it))
				return (true);
		}
		else if (phase == 2)
		{
			if (*it != '.')
			{
				if (from_zero)
				{
					phase = 4;
					continue ;
				}
				else
					return (true);
			}
			phase = 3;
		}
		else if (phase == 3)
		{
			if (!isdigit(*it))
			{
				if (*(it - 1) == '.')
					return (true);
				else
				{
					phase = 4;
					continue ;
				}
			}
		}
		else if (phase == 4)
		{
			if (*it != 'e' && *it != 'E')
				return (true);
			it++;
			if (!(it != input.end() && !(isspace(*it) && *it != '\v')))
				return (true);
			if (*it != '-' && *it != '+' && !isdigit(*it))
				return (true);
			phase = 5;
		}
		else if (phase == 5 && !isdigit(*it))
			return (true);
		it++;
	}
	Token	*new_token = new Token(input.substr(start - input.begin(), it - start), number, curr_parent);
	output.push_back(new_token);
	if (it != input.end())
		it--;
	if (curr_parent && curr_parent->_type == string)
		curr_parent = curr_parent->_parent;
	return (false);
}

int	Json::tokenizer(std::string& input, std::vector<Token *>& output)
{
	Token	curr_token("", undefined, NULL);
	Token	*curr_parent = NULL;
	for (std::string::iterator it = input.begin(); it != input.end(); it++)
	{
		if (isspace(*it) && *it != '\v')
			continue ;
		switch (*it)
		{
		case ']':
			if (curr_parent != NULL && curr_parent->_type == array)
			{
				curr_parent = curr_parent->_parent;
				if (curr_parent && curr_parent->_type != string && curr_parent->_type != array)
					return (1);
				else if (curr_parent->_type == string)
					curr_parent = curr_parent->_parent;
			}
			else
				return (1);
			break ;
		case '}':
			if (curr_parent != NULL && curr_parent->_type == object)
			{
				curr_parent = curr_parent->_parent;
				if (curr_parent != NULL && curr_parent->_type != string)
					return (1);
				else if (curr_parent && curr_parent->_type == string)
					curr_parent = curr_parent->_parent;
			}
			else
				return (1);
			break ;
		case '{':
			if (!is_values_parent_valid(curr_parent, false))
				return (1);
			curr_token._type = object;
			curr_token._parent = curr_parent;
			curr_parent = new Token(curr_token);
			output.push_back(curr_parent);
			break;
		case '[':
			if (!is_values_parent_valid(curr_parent, false))
				return (1);
			curr_token._type = array;
			curr_token._parent = curr_parent;
			curr_parent = new Token(curr_token);
			output.push_back(curr_parent);
			break;
		case '"':
			it++;
			if (!is_values_parent_valid(curr_parent, true) || do_string(input, it, output, curr_parent))
				return (1);
			break;
		case ',':
			if (curr_parent && curr_parent->_type != object && curr_parent->_type != array)
				return (1);
			break ;
		case ':':
			if (curr_parent->_type != string)
				return (1);
			break ;
		default:
			if (*it == '-' || isdigit(*it))
			{
				if (!is_values_parent_valid(curr_parent, false) || do_number(input, it, output, curr_parent))
					return (1);
			}
			else if (check_bool(input, it, output, curr_parent))
				return (1);
			break ;
		}
	}
	return (0);
}
