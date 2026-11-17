#include "includes/json.hpp"
/*

{
	{
		"true" : true,
		"false" : false,
		"null" : null
	},
	[
		"hello world",
		12,
		"test"
	],
	1.1e07,
	6.7,
	-5
}



*/

int main(void)
{
	t_token exemple;
	exemple.parent = NULL;
	exemple.type = object;
	exemple.token = "";

		t_token exemple_child1;
		exemple_child1.parent = &exemple;
		exemple_child1.type = object;
		exemple_child1.token = "";

			t_token exemple_child1_child1;
			exemple_child1.parent = &exemple_child1;
			exemple_child1.type = ttrue;
			exemple_child1.token = "";

				t_token exemple_child1_child1_child1;
				exemple_child1.parent = &exemple_child1;
				exemple_child1.type = ttrue;
				exemple_child1.token = "";

			t_token exemple_child1_child2;
			exemple_child1.parent = &exemple_child1;
			exemple_child1.type = tfalse;
			exemple_child1.token = "";

				t_token exemple_child1_child2_child1;
				exemple_child1.parent = &exemple_child1;
				exemple_child1.type = tfalse;
				exemple_child1.token = "";

			t_token exemple_child1_child3;
			exemple_child1.parent = &exemple_child1;
			exemple_child1.type = tnull;
			exemple_child1.token = "";

				t_token exemple_child1_child3_child1;
				exemple_child1.parent = &exemple_child1;
				exemple_child1.type = tnull;
				exemple_child1.token = "";

		t_token exemple_child2;
		exemple_child2.parent = &exemple;
		exemple_child2.type = array;
		exemple_child2.token = "";

			t_token exemple_child2_child1;
			exemple_child2.parent = &exemple;
			exemple_child2.type = string;
			exemple_child2.token = "hello world";

			t_token exemple_child2_child2;
			exemple_child2.parent = &exemple;
			exemple_child2.type = number;
			exemple_child2.token = "12";

			t_token exemple_child2_child3;
			exemple_child2.parent = &exemple;
			exemple_child2.type = string;
			exemple_child2.token = "test";

		t_token exemple_child3;
		exemple_child3.parent = &exemple;
		exemple_child3.type = number;
		exemple_child3.token = "-5";

		t_token exemple_child4;
		exemple_child4.parent = &exemple;
		exemple_child4.type = number;
		exemple_child4.token = "6.7";

		t_token exemple_child5;
		exemple_child5.parent = &exemple;
		exemple_child5.type = number;
		exemple_child5.token = "1.1e07";

	return (0);
}