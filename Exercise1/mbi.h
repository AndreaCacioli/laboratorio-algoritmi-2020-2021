#ifndef SOME_DIFFICULT_NAME_HARD_TO_REMEMBER
#define SOME_DIFFICULT_NAME_HARD_TO_REMEMBER


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

//Uncomment this if you want to perform unit tests on the sub-functions that make up the library  
#define SUB_TESTS


//Uncomment this if you want some of the functions to write to the screen
//#define VERBOSE_OUTPUT

/*
    * The function bi performs a binary-insertion sort:
    *   Similarly to the classic insertion sort a previously sorted part of the array (v) is given.
    *   The first element of the array is selected from just out of the sorted part.
    *   A new position is then found using binary search across the first part of the array
    * Specifications:
    *         Binary search is implemented recursively
*/
extern void* bi(void* v,int (*cmpfnc)(void*, void*), int size, int type_size);

/*
    * The function m performs a merge sort:
    *   The array (v) is recursively split into subarrays of half length until
    *   a unitary length is reached. Then the two subarrays are merged together
    *   maintaining the order specified by the comparator function
    *   size is the number of elements in the array
    *   type_size is the size in bytes of a single element
*/
extern void* m(void* v,int (*cmpfnc)(void*, void*), int size, int type_size, int k);

#ifdef SUB_TESTS
extern void swap(void* a, void* b, int type_size);
extern void copy_bytes(void* v, void* w, int type_size);
extern int binarySearch(void* arr, int (*cmpfnc)(void*, void*), int l, int r, void* x, int type_size);
extern void* merge(void* v, void* w, int v_size, int w_size, int (*cmpfnc)(void*, void*), int type_size);
#endif

#endif