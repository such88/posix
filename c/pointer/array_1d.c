#include<stdio.h>

void reverse_array(int *arr, int len){
    int temp;
    for(int i=0, j=len-1; i<j; i++,j--){
        arr[i] = arr[i] + arr[j];
        arr[j] = arr[i] - arr[j];
        arr[i] = arr[i] - arr[j];
    }
}

int main(){

    int arr[5] = {1, 2, 3, 4, 5};
    int *ptr = arr; // ptr is pointing to the first element of the array

    printf("Elements of the array: ");
    for(int i = 0; i < 5; i++){
        printf("%d ", *ptr); // dereferencing the pointer to get the value
        ptr++; // moving the pointer to the next element
    }
    printf("\n");

    reverse_array(arr,sizeof(arr)/sizeof(arr[0]));
    for(int i = 0; i < 5; i++){
        printf("%d ", arr[i]); // dereferencing the pointer to get the value
    }
    printf("\n");

    return 0;
}