#include<stdio.h>
#include<stdlib.h>
#include "memvis.h"

int main(){

    int x = 100, y = 101, z = 102;
    int* b[3];
    b[0] = &x;
    b[1] = &y;
    b[2] = &z;

    printf("&b = %p\n", &b);
    printf("b = %p\n", b);
    printf("b[0] = %p\n", b[0]);
    printf("b[1] = %p\n", b[1]);
    printf("b[0][0] = %d\n", *(b[0]));
    printf("b[1][0] = %d\n", b[1][0]);
    memvis(&b, ARRAY_OF_N_POINTER_TO_INTEGER, 3);

/* =====================================================================*/

    int xa[] = {1,2,3,4,5};
    memvis(xa, INTEGER_ARRAY, sizeof(xa)/sizeof(int));

/* =====================================================================*/

    int **pp = NULL;
    int *sp = NULL;
    sp = (int*)malloc(sizeof(int));
    *sp = 3784;

    pp = &sp;

    memvis(&pp, POINTER_TO_POINTER_TO_INTEGER, 0);
    free(*pp);

 /*=====================================================================*/


    int tmp_val = 0x12345678;
    memvis(&tmp_val, INTEGER, 0);
    return 0;
}

