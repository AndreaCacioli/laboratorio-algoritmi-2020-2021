#include <stdio.h>
#include <stdlib.h>
#include "mbi.h"

typedef struct line
{
    long id;
    char* c;
    int n;
    float f;
}line;

int main(int argc, char** args)
{
    FILE* file = fopen("./records.csv", "r");
    
    int prova;
    char* c = malloc(30);
    fscanf(file,"%d,", &prova);
    fscanf(file,"%s,", c);

    printf("%d\n", prova);
    puts(c);


    line* lines = malloc(20000000 * sizeof(line));
    int i = 0;
    /*while(!feof(file))
    {
        fscanf(file,"%d,%s,%d,%f\n", &lines[i].id, lines[i].c, &lines[i].n, &lines[i].f);
        //TODO read string char by char
        printf("%d,%s,%d,%f\n", lines[i].id, lines[i].c, lines[i].n, lines[i].f);
        printf("%f %%\n", i/200000.0);
        i++;
    }*/
    printf("Done!\n");
    fclose(file);
}