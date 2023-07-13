// gcc lht.c -ljson-c -o lht

#include <stdio.h>
#include <json-c/json.h>
#include <json-c/linkhash.h>

int 
main(void)
{
   struct json_object_iterator it;
   struct json_object_iterator itEnd;

   char *schedule = "/etc/thermostatd/schedule.json";

   json_object *root = json_object_from_file(schedule);
   lh_table *schedule_hash = json_object_get_object(root);

   struct lh_entry *setpoint = lh_table_lookup_entry(schedule_hash, "setPoint1");

   printf("key is %s\n", (char *)setpoint->k);


   // it = json_object_iter_init_default();
   /* it = json_object_iter_begin(root);
   itEnd = json_object_iter_end(root);

   while (!json_object_iter_equal(&it, &itEnd))
   {
      const char* key = json_object_iter_peek_name(&it);
      json_object* val = json_object_iter_peek_value(&it);
      printf("%s  -> %s\n", key, json_object_get_string(val));
      json_object_iter_next(&it);
   } */
   json_object_put(root);
   return 0;
}
