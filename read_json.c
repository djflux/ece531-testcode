#include <stdio.h>
#include <json-c/json.h>

int
main(void)
{
   json_object *root = json_object_from_file("/home/vagrant/code/ece531-final/config/thermostatd.json");
   printf("The json file:\n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_NOSLASHESCAPE));

   printf("The json file:\n\n%s\n", json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY|JSON_C_TO_STRING_NOSLASHESCAPE));
   json_object_put(root);
   return 0;
}
