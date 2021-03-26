#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "edit.h"

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
void free_mat(int** m, int rows)
{
    for(int i = 0; i < rows; i++)
    {
        free(m[i]);
    }
    free(m);
}

void test_edit_distance()
{
    assert(edit_distance("", "", 0, 0) == 0);
    assert(edit_distance("casa", "cassa", 4, 5) == 1);
    assert(edit_distance("casa", "cara", 4, 4) == 2);
    assert(edit_distance("vinaio", "vino", 6, 4) == 2);
    assert(edit_distance("tassa", "passato", 5, 7) == 4);
    assert(edit_distance("pioppo", "pioppo", 6, 6) == 0);
}
void test_edit_distance_dyn()
{
    int** mat = NULL;

    mat = setup_mat(0, 0);
    assert(edit_distance_dyn("", "", 0, 0, mat) == 0);
    free_mat(mat, 0);

    mat = setup_mat(4, 5);
    assert(edit_distance_dyn("casa", "cassa", 4, 5, mat) == 1);
    free_mat(mat, 4);

    mat = setup_mat(4, 4);
    assert(edit_distance_dyn("casa", "cara", 4, 4, mat) == 2);
    free_mat(mat, 4);

    mat = setup_mat(6, 4);
    assert(edit_distance_dyn("vinaio", "vino", 6, 4, mat) == 2);
    free_mat(mat, 6);

    mat = setup_mat(5, 7);
    assert(edit_distance_dyn("tassa", "passato", 5, 7, mat) == 4);
    free_mat(mat, 5);

    mat = setup_mat(6, 6);
    assert(edit_distance_dyn("pioppo", "pioppo", 6, 6, mat) == 0);
    free_mat(mat, 6);
}

int main(int argc, char* args[])
{
    test_edit_distance();
    test_edit_distance_dyn();
    return 0;
}