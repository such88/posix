#include <stdio.h>
int set_get_global_static();

static int g_count = 0; // global static variable to keep track of the count
void set_global_static(int value){
    g_count = value; // setting the count to the provided value
}
int get_global_static(){
    g_count++; // incrementing the count
    return g_count; // returning the count
}

void set_local_static(int value){
    //l_count = value; // error as l_count is not declared in this scope
}
int get_local_static(){
    static int l_count = 0; // static variable to keep track of the count
    l_count++; // incrementing the count
    return l_count; // returning the count
}

int main(){

    int get_local_static_return_value; // variable to store the return value of the function
    get_local_static();
    get_local_static();
    get_local_static();
    get_local_static_return_value = get_local_static(); // calling the function to get the local static count
    printf("Local Static Count: %d\n", get_local_static_return_value); // printing the local static count

    int get_global_static_return_value; // variable to store the return value of the function
    get_global_static();
    set_global_static(100); // setting the global static count to 100
    get_global_static();
    get_global_static_return_value = get_global_static(); // calling the function to get the global static count
    printf("Global Static Count: %d\n", get_global_static_return_value); // printing the global static count

    get_global_static_return_value = set_get_global_static(); // calling the function to set and get the global static count
    printf("Global Static Count: %d\n", get_global_static_return_value); // printing the global static count
    return 0;
}