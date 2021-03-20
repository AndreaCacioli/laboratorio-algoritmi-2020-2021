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

void test_sort_empty_array() 
{
    int a[] = {};
    assert(a == bi(a, cmp, 0, sizeof(int)));
    assert(a == m(a, cmp, 0, sizeof(int)));
}

void test_sort_null_array() 
{
    int* a = NULL;
    assert(a == bi(a, cmp, 0, sizeof(int)));
    assert(a == m(a, cmp, 0, sizeof(int)));
}
void test_sort_sorted_array() 
{
    int a[] = {1,3,5,7,11};
    int* b = bi(a,cmp, 5, sizeof(int));
    int* c = m(a,cmp, 5, sizeof(int));
    for(int i = 0; i < 5; i++)
    {
        assert(a[i] == b[i]);
        assert(a[i] == c[i]);
    }
}
 
int main(int argc, char** argv) 
{
    test_sort_empty_array();
    test_sort_null_array();
    test_sort_sorted_array();
    return 0;
}
