#include "headerFiles/jsonConverter.h"

void jsonParserPayload(char *json_string){
cJSON *name = NULL;
cJSON *root = cJSON_Parse(json_string);

root = cJSON_GetObjectItem(root, "payload");

name = cJSON_GetObjectItem(root, "current_x");
current_x = name->valueint;

name = cJSON_GetObjectItem(root, "current_y");
current_y = name->valueint;

name = cJSON_GetObjectItem(root, "direction");
direction = name->valuestring[0];

name = cJSON_GetObjectItem(root, "field_type");
field_type = name->valuestring[0];
}

int getCurrentX(){
	return current_x;
}

int getCurrentY(){
	return current_y;
}

char getDirection(){
	return direction;
}

char getFieldType(){
	return field_type;
}
