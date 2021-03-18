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


/*
    * The function bi performs a binary-insertion sort:
    *   Similarly to the classic insertion sort a previously sorted part of the array is given.
    *   The first element of the array is selected from just out of the sorted part.
    *   A new position is then found using binary search across the first part of the array
    * Specifications:
    *         Binary search is implemented recursively
    * 
*/
extern void* bi(void* v,int (*cmpfnc)(void*, void*), int size, int type_size);


#endif