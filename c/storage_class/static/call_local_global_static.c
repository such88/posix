#include "static.h"
#include <stdio.h>
int set_get_global_static(){
    printf("set global static variable functions\n");
    set_global_static(500); // calling the function to set the global static count
    get_global_static(); // calling the function to get the global static count
    get_global_static();
    return get_global_static();

}