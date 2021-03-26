#include <math.h>
#include <stddef.h>
#define INT_MAX 2147483647
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

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