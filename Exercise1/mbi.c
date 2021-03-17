#include "mbi.h"
#include <stdlib.h>
#include <stdio.h>

void swap(void* a, void* b, int type_size)
{
    unsigned char* p = a, *q = b, tmp;
    for (int i = 0; i < type_size; i++)
    {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}

int binarySearch(void* arr, int (*cmpfnc)(void*, void*), int l, int r, void* x, int type_size) 
{ 
    if (r >= l) 
    { 
        int mid = l + (r - l) / 2; 

        
        if (cmpfnc(arr + type_size * mid,x) == 0)
            return mid; 

        
        if (cmpfnc(arr + type_size * mid, x) > 0) 
            return binarySearch(arr, cmpfnc, l, mid - 1, x, type_size); 

        return binarySearch(arr, cmpfnc, mid + 1, r, x, type_size); 
    } 

    return l + (r - l) / 2; 
} 

void* bi(void* v,int (*cmpfnc)(void*, void*), int size, int type_size)
{
    if(size == 0) return v;
    else if (v == NULL) return NULL;

    for(int i = 1; i < size; i++)
    {
        int start = 0, end = i-1;

        int pos = binarySearch(v, cmpfnc, start, end, v + i * type_size , type_size);

        for(int k = i; k > pos; k--)
        {
            swap(v + k * type_size, v + (k - 1) * type_size, type_size);
        }
        
    }

    return v;
}



