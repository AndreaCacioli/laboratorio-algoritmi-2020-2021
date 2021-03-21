#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    assert(a == m(a, cmp, 0, sizeof(int),0));
}

void test_sort_null_array() 
{
    int* a = NULL;
    assert(a == bi(a, cmp, 0, sizeof(int)));
    assert(a == m(a, cmp, 0, sizeof(int),0));
}
void test_sort_sorted_array() 
{
    int a1[] = {1,3,5,7,11};
    int a2[] = {1,3,5,7,11};
    int* b = bi(a1,cmp, 5, sizeof(int));
    int* c = m(a2,cmp, 5, sizeof(int), 0);
    for(int i = 0; i < 5; i++)
    {
        assert(a1[i] == b[i]);
        assert(a2[i] == c[i]);
    }
}
void test_sort_reverse_sorted_array() 
{
    int a1[] = {9,6,3,2,1};
    int a2[] = {9,6,3,2,1};
    int* b = bi(a1,cmp, 5, sizeof(int));
    int* c = m(a2,cmp, 5, sizeof(int), 0);
    int d[] = {1,2,3,6,9};
    for(int i = 0; i < 5; i++)
    {
        assert(d[i] == b[i]);
        assert(d[i] == c[i]);
    }
}
void test_sort_random_array() 
{
    time_t t;
    srand((unsigned)time(&t));

    for(int j = 0; j<5;j++)
    {
        int* a1 = (int*) malloc(10 * sizeof(int));
        int* a2 = (int*) malloc(10 * sizeof(int));
        for(int i = 0; i < 10; i++)
        {
            a1[i] = rand() % 500;
            a2[i] = rand() % 500;
        }
        int* b = bi(a1,cmp, 10, sizeof(int));
        int* c = m(a2,cmp,10,sizeof(int), j);
        for(int i = 0; i < 9; i++)
        {
            assert(b[i] <= b[i + 1]);
            assert(c[i] <= c[i + 1]);
        }
        free(a1);
        free(a2);
    }

   
}
 
int main(int argc, char** argv) 
{
    test_sort_empty_array();
    test_sort_null_array();
    test_sort_sorted_array();
    test_sort_reverse_sorted_array();
    test_sort_random_array();
    return 0;
}
