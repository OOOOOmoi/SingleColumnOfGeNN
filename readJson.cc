#include <iostream>
#include <cJSON.h>

int main()
{
    cJSON* root=cJSON_Parse("jsonTest.json");
    return 0;
}