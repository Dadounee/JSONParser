#include "Json.hpp"

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

{"obj":{"true":true,"false":false,"null":null},"arr":["hello world",12,"test"],"exp" : 1.1e07,"float" : 6.7,"neg":-5}

*/

int main(void)
{
	std::string				input = "{\"obj\":{\"true\":true,\"false\":false,\"null\":null},\"arr\":[\"hello world\",12,\"test\"],\"exp\" : 1.1e07,\"float\" : 6.7,\"neg\":-5}";

	JsonData	*hoping_for_best = NULL;
	hoping_for_best = Json::convert(input);

	Json::display(*hoping_for_best);

	delete hoping_for_best;

	return (0);
}