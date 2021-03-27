#ifndef __EDIT_DISTANCE_STRINGS__
#define __EDIT_DISTANCE_STRINGS__
#include <stddef.h>

/************************************************************************
 * Andrea Cacioli's Edit Distance Library:
 *  Two recursive implementations of the algorithm to calculate edit 
 *  distance of two strings.
 * Dynamic version uses a matrix to store sub problems's solutions.
 *************************************************************************/

/*
    * The non-dynamic implementation: 
    *   a is the first string
    *   b is the second string
    *   len1 is the length of the first string
    *   len2 is the length of the second string
*/
extern int edit_distance(char* a, char* b, size_t len1, size_t len2);

/*
    * The dynamic implementation: 
    *   a is the first string
    *   b is the second string
    *   len1 is the length of the first string
    *   len2 is the length of the second string
    *   mat is an int matrix which needs to have at least len1 rows and len2 columns
*/
extern int edit_distance_dyn(char* a, char* b, size_t len1, size_t len2, int** mat);

//A couple of utility functions:
//  setup_mat dynamically allocates a matrix with given rows and columns
//  free_mat deallocates the previously allocated matrix
extern int** setup_mat(int rows, int columns);
void free_mat(int** m, int rows);

#endif