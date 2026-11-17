#include "json.hpp"

int	tokenizer(std::string input, std::vector<t_token>& output)
{
	std::string		curr_token = "";
	t_token_types	curr_type = undefined;
	t_token			*curr_parent = NULL;
	for (std::string::iterator it = input.begin(); it != input.end(); it++)
	{
		switch (*it)
		{
		case '}': case ']':
			if (curr_parent != NULL)
				curr_parent = curr_parent->parent;
			else
				return (1);
			break ;
		case '{':
			curr_token = "";
			curr_type = object;
			output.push_back();
			break;
		case '[':
			curr_token = "";
			curr_type = array;
			break;
		case '"':
			/* code */
			break;
		case '-':
			/* code */
			break;
		default:
			break;
		}
	}
}
