#include "../jsonConverter.c"
#include "headerFiles/jsonConverterTest.h"

void testJSONParser()
{
    char *json_string =
	"{\"status\": \"Success\", \"payload\": {\"name\": \"First world 31\", \"current_x\": 1, \"current_y\": 1, \"current_session\": \"012da2f9-1953-4305-bc4b-a0d09a8bd193\", \"direction\": \"W\", \"step\": 7, \"field_type\": \"grass\", \"field_bonus\": \"\"}}";

    char *names[] =
	{ "current_x", "current_y", "direction", "field_type" };
    printf("JSON:\n %s \n", json_string);
    printf("POBIERANE WARTOSCI:\n %s, %s, %s, %s \n", names[0], names[1],
	   names[2], names[3]);
    printf("ODCZYTANE WARTOSCI: \n");
    jsonParserPayload(json_string);
}
