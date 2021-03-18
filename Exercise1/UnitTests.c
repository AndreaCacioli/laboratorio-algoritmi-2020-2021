#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mbi.h"

int cmp(void* a, void* b)
{
    return *(int*)a - *(int*)b;
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
    int a[] = {1,3,6,8,10};
    int b[] = {3,11,34,49};
    int* t = merge(a,b,5,4,cmp,sizeof(int));
    for(int i = 0; i < 9; i++)
    {
        printf("%d\n", t[i]);
    }
    return 0;
}
