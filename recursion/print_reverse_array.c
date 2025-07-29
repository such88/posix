#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#define LENGTH 10

int ip_arr[LENGTH];

void print_reverse_array(int arr[], int len) {
    if (len <= 0) {
        return;
    }

    printf("%d ", arr[len-1]);
    print_reverse_array(arr, len -1);
}

int main(){
    int sum = 0;
    
    for(int i = 0; i < LENGTH; i++) {
        ip_arr[i] = rand() % 100; // Random integers between 0 and 99
    }
    printf("input arr: ");
    for(int i = 0; i < LENGTH; i++) {
        printf("%d ", ip_arr[i]);
    }

    printf("\n");
    print_reverse_array(ip_arr, LENGTH);
    return 0;
}