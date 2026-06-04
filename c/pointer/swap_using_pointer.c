#include<stdio.h>

void swap(int *p, int *q){

    *p = *p +*q;
    *q = *p-*q;
    *p= *p- *q;
}

int main(){

    int a = 2, b = 3;
    printf("Before swapping: a = %u, b = %u\n", a, b);
    swap(&a, &b);
    printf("Before swapping: a = %u, b = %u\n", a, b);
    return 0;

}