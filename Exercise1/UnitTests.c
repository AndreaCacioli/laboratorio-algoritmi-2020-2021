#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "mbi.h"

int cmp(void* a, void* b)
{
    return *(int*)a - *(int*)b;
}

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

int main(int argc, char** argv) 
{
    test_sort_empty_array();
    test_sort_null_array();

}