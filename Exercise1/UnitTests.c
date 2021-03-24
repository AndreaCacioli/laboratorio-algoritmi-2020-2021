#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "mbi.h"

 typedef struct _data
    {
        float f;
        int n;
    }data;

int cmp(void* a, void* b)
{
    return *(int*)a - *(int*)b;
}
int cmpfloat(void* a, void* b)
{
    return *(float*)a - *(float*)b;
}
int cmpstr(void* a, void* b)
{
    return strcmp(*(char**)a, *(char**)b);
}
int cmpdataint(void* a, void* b)
{
    return ((data*)a)->n - ((data*)b)->n;
}
int cmpdatafloat(void* a, void* b)
{
    return 10000 * (((data*)a)->f - ((data*)b)->f); //Multiply by 10000 to ensure the difference is visible in an int variable, for more precision increase the factor
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

void test_sort_float_array()
{
    float a1[] = {1.8,6.3,5.0,1.3};
    float a2[] = {1.8,6.3,5.0,1.3};

    float ans[] = {1.3, 1.8, 5.0, 6.3};

    bi(a1,cmpfloat,4, sizeof(float));
    m(a2,cmpfloat,4, sizeof(float), 0);
    for(int i  = 0; i < 4; i++)
    {
        assert(a1[i] == ans[i]);
        assert(a2[i] == ans[i]);
    }

}

void test_sort_string_array()
{
    char* a1[] = {"Jean", "Diluc", "Hu-Tao", "Barbara"};
    char* a2[] = {"Jean", "Diluc", "Hu-Tao", "Barbara"};
    char* ans[] = {"Barbara", "Diluc", "Hu-Tao", "Jean"};


    bi(a1, cmpstr, 4, sizeof(char*));
    m(a2, cmpstr, 4, sizeof(char*),0);


    for(int i = 0; i < 4; i++)
    {
        assert(strcmp(a1[i], ans[i]) == 0);
        assert(strcmp(a2[i], ans[i]) == 0);
    }
}


void test_sort_records()
{
    time_t t;
    srand((unsigned)time(&t));

    data v[4];
    v[0].f = 2.1;
    v[0].n = 4;
    v[1].f = 7.89;
    v[1].n = 5;
    v[2].f = 1.1;
    v[2].n = 0;
    v[3].f = 9.2;
    v[3].n = 3;

    m(v,cmpdataint,4,sizeof(data),rand()%4);

    for(int i = 0; i < 3; i++)
    {
        assert(v[i].n <= v[i+1].n);
    }

    m(v,cmpdatafloat,4,sizeof(data),rand()%4);

    for(int i = 0; i < 3; i++)
    {
        assert(v[i].f <= v[i+1].f);
    }

}



#ifdef SUB_TESTS
    void test_merge()
    {
        int v[8] = {1,4,7,8,2,3,6,78};
        int* p = &v[4];
        int ans[] = {1,2,3,4,6,7,8,78};
        merge(v,p,4,4,cmp,sizeof(int));
        for(int i = 0; i < 8; i++)
        {
            assert(v[i] == ans[i]);
        }
    }
#endif
 
int main(int argc, char** argv) 
{
    #ifdef SUB_TESTS
    test_merge();
    #endif
    test_sort_empty_array();
    test_sort_null_array();
    test_sort_sorted_array();
    test_sort_reverse_sorted_array();
    test_sort_random_array();
    test_sort_float_array();
    test_sort_string_array();
    test_sort_records();
    return 0;
}
