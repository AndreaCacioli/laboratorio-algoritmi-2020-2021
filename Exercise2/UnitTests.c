#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include "edit.h"

int main(int argc, char* args[])
{
    assert(edit_distance("casa", "cassa", 4, 5) == 1);
    assert(edit_distance("casa", "cara", 4, 4) == 2);
    assert(edit_distance("vinaio", "vino", 6, 4) == 2);
    assert(edit_distance("tassa", "passato", 5, 7) == 4);
    assert(edit_distance("pioppo", "pioppo", 6, 6) == 0);

    return 0;
}