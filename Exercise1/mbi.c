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


void copy_bytes(void* v, void* w, int type_size) //Copies the content of v into w
{
    unsigned char* a = v, *b = w;
    for(int i = 0; i < type_size; i++)
    {
        *(b+i) = *(a+i);
    }
}

void* merge(void* v, void* w, int v_size, int w_size, int (*cmpfnc)(void*, void*), int type_size) //merges two sorted arrays keeping them sorted
{
    int i = 0, j = 0, k = 0;
    int length = v_size + w_size;
    void* arr = malloc(length * type_size);

    while(k < length)
    {
        if(j == w_size)
        {
            copy_bytes(v + i * type_size, arr + k * type_size, type_size);
            if(i < v_size) i++;
        }
        else if(i == v_size)
        {
            copy_bytes(w + j * type_size, arr + k * type_size, type_size);
            if(j < w_size) j++;
        }
        else if(cmpfnc(v + i * type_size, w + j * type_size) < 0)
        {
            copy_bytes(v + i * type_size, arr + k * type_size, type_size);
            if(i < v_size) i++;
        }
        else if(cmpfnc(v+ i * type_size, w + j * type_size) >= 0)
        {
            copy_bytes(w + j * type_size, arr + k * type_size, type_size);
            if(j < w_size) j++;
        }
        k++;
    }
    return arr;
}

void* m(void* v,int (*cmpfnc)(void*, void*), int size, int type_size)
{   
    if(v == NULL) return NULL;
    if(size == 0) return v;

    void* mid = v + (size  / 2) * type_size;
    if(size > 1)
    {
        return merge(m(v, cmpfnc, size/2, type_size), m(mid, cmpfnc, (size+1)/2, type_size), size/2, (size+1)/2, cmpfnc, type_size);
    }
    else
    {
        return v;
    }
}


