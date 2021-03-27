#include <math.h>
#include <stddef.h>
#include <stdlib.h>

#define INT_MAX 2147483647
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

/*
    * The non-dynamic implementation: 
    *   a is the first string
    *   b is the second string
    *   len1 is the length of the first string
    *   len2 is the length of the second string
*/
int edit_distance(char* a, char* b, size_t len1, size_t len2)
{
    if(len1 == 0) return (int)len2;
    if(len2 == 0) return (int)len1;
    else
    {
        int d_no_op = a[0] == b[0] ? edit_distance(a + 1, b + 1, len1 - 1, len2 - 1) : INT_MAX;
        int d_del = 1 + edit_distance(a, b + 1, len1, len2 - 1);
        int d_ins = 1 + edit_distance(a + 1, b , len1 - 1, len2);
        return MIN(d_no_op, MIN(d_del, d_ins));
    }
}

/*
    * The dynamic implementation: 
    *   a is the first string
    *   b is the second string
    *   len1 is the length of the first string
    *   len2 is the length of the second string
    *   mat is an int matrix which needs to have at least len1 rows and len2 columns
*/
int edit_distance_dyn(char* a, char* b, size_t len1, size_t len2, int** mat)
{
    if(len1 == 0) return (int)len2;
    if(len2 == 0) return (int)len1;
    else
    {
        if(mat[len1 - 1][len2 - 1] == -1)
        {
            int d_no_op = a[0] == b[0] ? edit_distance_dyn(a + 1, b + 1, len1 - 1, len2 - 1, mat) : INT_MAX;
            int d_del = 1 + edit_distance_dyn(a, b + 1, len1, len2 - 1, mat);
            int d_ins = 1 + edit_distance_dyn(a + 1, b , len1 - 1, len2, mat);
            int res = MIN(d_no_op, MIN(d_del, d_ins));
            mat[len1 - 1][len2 - 1] = res;
            return res;
        }
        else return mat[len1 - 1][len2 - 1];
        
    }
}


//A couple of utility functions:
//  setup_mat dynamically allocates a matrix with given rows and columns
int** setup_mat(int rows, int columns)
{
    int** m = malloc(rows * sizeof(int*));
    for(int i = 0; i < rows; i++)
    {
        m[i] = malloc(columns * sizeof(int));
        for(int j = 0; j < columns; j++)
        {
            m[i][j] = -1;
        }
    }
    return m;
}

//  free_mat deallocates the previously allocated matrix
void free_mat(int** m, int rows)
{
    for(int i = 0; i < rows; i++)
    {
        free(m[i]);
    }
    free(m);
}