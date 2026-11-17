#include "includes/json.hpp"
#include "Token.hpp"
/*

{
	"obj" : {
		"true" : true,
		"false" : false,
		"null" : null
	},
	"arr" : [
		"hello world",
		12,
		"test"
	],
	"exp" : 1.1e07,
	"float" : 6.7,
	"neg" : -5
}



*/

int main(void)
{
	std::vector<Token *> raw;

	Token *exemple = new Token("", object, NULL);

	raw.push_back(exemple);

		Token *exemple_child1 = new Token("obj", string, exemple);
		raw.push_back(exemple_child1);

			Token *exemple_child1_child1 = new Token("", object, exemple_child1);
			raw.push_back(exemple_child1_child1);

				Token *exemple_child1_child1_child1 = new Token("true", string, exemple_child1_child1);
				raw.push_back(exemple_child1_child1_child1);

					Token *exemple_child1_child1_child1_child1 = new Token("", ttrue, exemple_child1_child1_child1);
					raw.push_back(exemple_child1_child1_child1_child1);

				Token *exemple_child1_child1_child2 = new Token("false", string, exemple_child1_child1);
				raw.push_back(exemple_child1_child1_child2);

					Token *exemple_child1_child1_child1_child2 = new Token("", tfalse, exemple_child1_child1_child2);
					raw.push_back(exemple_child1_child1_child1_child2);

				Token *exemple_child1_child1_child3 = new Token("null", string, exemple_child1_child1);
				raw.push_back(exemple_child1_child1_child3);

					Token *exemple_child1_child1_child1_child3 = new Token("", tnull, exemple_child1_child1_child3);
					raw.push_back(exemple_child1_child1_child1_child3);

		Token *exemple_child2 = new Token("arr", string, exemple);
		raw.push_back(exemple_child2);
		
			Token *exemple_child2_child1 = new Token("", array, exemple_child2);
			raw.push_back(exemple_child2_child1);

				Token *exemple_child2_child1_child1 = new Token("hello world", string, exemple_child2_child1);
				raw.push_back(exemple_child2_child1_child1);

				Token *exemple_child2_child1_child2 = new Token("12", number, exemple_child2_child1);
				raw.push_back(exemple_child2_child1_child2);

				Token *exemple_child2_child1_child3 = new Token("test", string, exemple_child2_child1);
				raw.push_back(exemple_child2_child1_child3);

		Token *exemple_child3 = new Token("neg", string, exemple);
		raw.push_back(exemple_child3);

			Token *exemple_child3_child1 = new Token("-5", number, exemple_child3);
			raw.push_back(exemple_child3_child1);

		Token *exemple_child4 = new Token("float", string, exemple);
		raw.push_back(exemple_child4);

			Token *exemple_child4_child1 = new Token("6.7", number, exemple_child4);
			raw.push_back(exemple_child4_child1);

		Token *exemple_child5 = new Token("exp", string, exemple);
		raw.push_back(exemple_child5);

			Token *exemple_child5_child1 = new Token("1.1e07", number, exemple_child5);
			raw.push_back(exemple_child5_child1);

	return (0);
}