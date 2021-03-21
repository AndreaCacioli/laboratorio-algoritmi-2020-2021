#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mbi.h"

typedef struct line
{
    long id;
    char* c;
    int n;
    float f;
}line;

void print_line(line l);
line* copy_lines(line* lines);

int cmpint(void* a, void* b)
{
    return ((line*)a)->n - ((line*)b)->n;
}
int cmpstr(void* a, void* b)
{
    return strcmp(((line*)a)->c, ((line*)b)->c);
}
int cmpfloat(void* a, void* b)
{
    return ((line*)a)->f - ((line*)b)->f;
}

int main(int argc, char** args)
{
    FILE* file = fopen("./records.csv", "r");

    line* lines = malloc(20000000 * sizeof(line));
    int i = 0;
    while(!feof(file))
    {
        fscanf(file,"%ld,", &lines[i].id);

        lines[i].c = (char*)malloc(30);

        for(int j = 0; j < 30; j++)
        {
            char character = ' ';
            fscanf(file,"%c", &character);
            if(character == ',') break;
            else lines[i].c[j] = character;
        }

        fscanf(file,"%d,%f", &lines[i].n, &lines[i].f);
        fflush(stdout);
        printf("\r%f %%", i/200000.0);
        i++;
    }
    printf("Done!\n");
    printf("Showing a couple data that has been stored:\n");
    for (int i = 0; i < 21; i++)
    {
        print_line(lines[i]);
    }

    FILE* results = fopen("results.csv", "w");

    time_t simulation_start = time(&simulation_start);
    time_t simulation_end = time(&simulation_end);
    for (int k = 0; k < 20; k++)
    {
        time_t starting_time = 0;
        time_t end_time = 0;

        line* l = NULL;

        //Sorting by Field1
        l = copy_lines(lines);
        time(&starting_time);
        m(l, cmpstr, 20000000, sizeof(line), k);
        time(&end_time);
        fprintf(results, "%ld,", end_time - starting_time);
        printf("k = %d, sorting by string, time:\t%ld\n",k, end_time - starting_time);

        //Sorting by Field2
        time(&starting_time);
        m(l, cmpint, 20000000, sizeof(line), k);
        time(&end_time);
        fprintf(results, "%ld,", end_time - starting_time);
        printf("k = %d, sorting by int, time:\t%ld\n",k, end_time - starting_time);

        //Sorting by Field3
        time(&starting_time);
        m(l, cmpint, 20000000, sizeof(line), k);
        time(&end_time);
        fprintf(results, "%ld\n", end_time - starting_time);
        printf("k = %d, sorting by float, time:\t%ld\n",k, end_time - starting_time);

        simulation_end = time(&simulation_end);
        if(simulation_end - simulation_start >= (20 * 60))
        {
            printf("20 minutes have passed...\nInterrupting the simulations, results can be found in results.csv\n");
            free(lines);
            free(l);
            fclose(file);
            fclose(results);
            return 0;
        }
    }
    

    free(lines);
    fclose(file);
    fclose(results);
}

void print_line(line l)
{
    printf("id: %ld\t Word: %s\t\t int: %d\t float: %2f\n", l.id, l.c, l.n, l.f);
}
line* copy_lines(line* lines)
{
    line* ret = (line*)malloc(20000000 * sizeof(line));
    for(int i = 0; i < 20000000; i++)
    {
        ret[i].id = lines[i].id;
        ret[i].c = lines[i].c;
        ret[i].n = lines[i].n;
        ret[i].f = lines[i].f;
        fflush(stdout);
        printf("\rCopying data: %3.2f%%",i/200000.0);
    }
    printf("\r");
    return ret;
}