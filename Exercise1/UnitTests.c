#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mbi.h"

int cmp(void* a, void* b)
{
    return *(int*)a - *(int*)b;
}

int revcmp(void* a, void* b)
{
    return *(int*)b - *(int*)a;
}
/*
void test_sort_empty_array() 
{
    int a[] = {};
    assert(a == bi(a, cmp, 0, sizeof(int)));
}

void test_sort_null_array() 
{
    int* a = NULL;
    assert(a == bi(a, cmp, 0, sizeof(int));
}
*/
int main(int argc, char** argv) 
{
    //test_sort_empty_array();
    //test_sort_null_array();
    int c[] = {1,3,2,4,5,8,3,7,0,14,15,99,43,21,7,6,8,9,42,11,14,67,89,4,1,72,13,69};

    int* t = m(c,revcmp,28,sizeof(int));
    for(int i = 0; i < 28; i++)
    {
        printf("%d\n", t[i]);
    }
    return 0;
}
