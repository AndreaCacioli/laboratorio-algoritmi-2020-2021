#ifndef __EDIT_DISTANCE_STRINGS__
#define __EDIT_DISTANCE_STRINGS__
#include <stddef.h>


extern int edit_distance(char* a, char* b, size_t len1, size_t len2);
extern int edit_distance_dyn(char* a, char* b, size_t len1, size_t len2, int** mat);

#endif