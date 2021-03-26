#ifndef __EDIT_DISTANCE_STRINGS__
#define __EDIT_DISTANCE_STRINGS__
#include <stddef.h>


extern int edit_distance(char* a, char* b, size_t len1, size_t len2);
extern int edit_distance_dyn(char* a, char* b, size_t len1, size_t len2, int** mat);
extern int** setup_mat(int rows, int columns);
void free_mat(int** m, int rows);

#endif