#include "mbi.h"
#include <stdlib.h>
#include <stdio.h>

/**********************************************************************************************
    *
    * A library of functions written by Andrea Cacioli to sort arrays of any primitive type
    * or custom writted records provided that a comparator function pointer is specified for
    * the algorithm to know the priority of one object compared to the other, similar to how
    * the C-specific qsort function handles this kind of comparison.
    * Therefore the size of the array needs to be known at first as well as the size in bytes 
    * of each individual element.
    * 
***********************************************************************************************/

//A simple function that swaps the content of two elements of an array of unknown type
//  a is a pointer to the memory area of the first variable/record
//  b is a pointer to the memory area of the second variable/record
//  type_size is the size in bytes of a and b
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

//A simple function that copies the content of one variable/record to another variable/record of unknown type
//  v is a pointer to the memory area containing our data
//  w is a pointer to the memory area where we want to copy our data to
//  type_size is the size in bytes of v and w
void copy_bytes(void* v, void* w, int type_size) //Copies the content of v into w
{
    unsigned char* a = v, *b = w;
    for(int i = 0; i < type_size; i++)
    {
        *(b+i) = *(a+i);
    }
}

//An auxiliary function that looks for the position of a previously sorted array in which we can put a given object in order to keep the array sorted
//  arr is the array
//  cmpfnc is a int function wich takes as input two pointers to the elements and returns:
//         0 if the two elements are to be considered equal
//         a value < 0 if the first element is to be placed BEFORE the second one
//         a value > 0 if the first element is to be placed AFTER the second one
//  l is the left bound of the array
//  r is the right bound of the array
//  x is a pointer to the memory area containing the object we have to insert
//  type_size is the size in bytes of each element
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

//A function that merges two previously sorted arrays into one that is also sorted
//The kth element of the final array is chosen after finding the "smaller" between the ith element of the first array and the jth element of the second one
//Then, depending on which one between i and j has been chosen, it is incremented by one effectively preventing an element to be selected twice
//      v is a pointer to the memory area of the first array
//      w is a pointer to the memory area of the second array
//      v_size is the number of elements of the first array
//      w_size is the number of elements of the second array
//      cmpfnc is a int function wich takes as input two pointers to the elements and returns:
//          0 if the two elements are to be considered equal
//          a value < 0 if the first element is to be placed BEFORE the second one
//          a value > 0 if the first element is to be placed AFTER the second one
//      type_size is the size in bytes of a and b
void* merge(void* v, void* w, int v_size, int w_size, int (*cmpfnc)(void*, void*), int type_size)
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

/*
    * The function bi performs a binary-insertion sort:
    *   Similarly to the classic insertion sort a previously sorted part of the array (v) is given.
    *   The first element of the array is selected from just out of the sorted part.
    *   A new position is then found using binary search across the first part of the array
*/
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

/*
    * The function m performs a merge sort:
    *   The array (v) is recursively split into subarrays of half length until
    *   a unitary length is reached. Then the two subarrays are merged together
    *   maintaining the order specified by the comparator function
    *   size is the number of elements in the array
    *   type_size is the size in bytes of a single element
*/
void* m(void* v,int (*cmpfnc)(void*, void*), int size, int type_size, int k)
{   
    if(v == NULL) return NULL;
    if(size == 0) return v;

    void* mid = v + (size  / 2) * type_size;
    if(size > k) //If array is long we use merge sort
    {
        if(size > 1)
        {
            return merge(m(v, cmpfnc, size/2, type_size, k), m(mid, cmpfnc, (size+1)/2, type_size, k), size/2, (size+1)/2, cmpfnc, type_size);
        }
        else
        {
            return v;
        }
    }
    else return bi(v,cmpfnc,size,type_size);//When array is short enough we perform Binary-Insertion
    
}



