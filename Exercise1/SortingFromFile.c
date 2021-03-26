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
}Line;

void print_line(Line l);
void copy_lines(Line* lines, Line* ret);

int cmpint(void* a, void* b)
{
    return ((Line*)a)->n - ((Line*)b)->n;
}
int cmpstr(void* a, void* b)
{
    return strcmp(((Line*)a)->c, ((Line*)b)->c);
}
int cmpfloat(void* a, void* b)
{
    return (((Line*)a)->f <= ((Line*)b)->f) ? -1 : 1;
}

int main(int argc, char** args)
{
    if(argc != 4) 
    {
        fprintf(stderr,"Please specify the starting and ending values of k and the time limit in minutes\n");
        return 1;
    }

    FILE* file;
    FILE* results = fopen("results.csv", "w");
    Line* l = (Line*)malloc(20000000 * sizeof(Line));
    int i = 0;

    if((file = fopen("./records.csv", "r")) == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        return 1;
    }
    printf("File found!\n");

    Line* lines = malloc(20000000 * sizeof(Line));
    
    printf("Populating the array...\n");
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
        printf("\r%3.2f %%", i/200000.0);
        i++;
    }
    printf("Done!\n");
    printf("Showing a couple data that has been stored:\n");
    for (int i = 0; i < 21; i++)
    {
        print_line(lines[i]);
    }

    time_t simulation_start = time(&simulation_start);
    time_t simulation_end = time(&simulation_end);
    int start = atoi(args[1]);
    int end = atoi(args[2]);
    int maxTime = atoi(args[3]);

    for (int k = start; k < end; k++)
    {
        printf("Starting to sort for k = %d\n", k);
        time_t starting_time = 0;
        time_t end_time = 0;
        copy_lines(lines, l);

        //Sorting by Field1
        time(&starting_time);
        m(l, cmpstr, 20000000, sizeof(Line), k);
        time(&end_time);
        fprintf(results, "%ld,", end_time - starting_time);
        printf("k = %d, sorting by string, time:\t%ld\n",k, end_time - starting_time);
        printf("Showing a couple data that has been stored:\n");
        for (int i = 0; i < 21; i++)
        {
            print_line(l[i]);
        }
        printf("\n\n");

        //Sorting by Field2
        //copy_lines(lines, l);
        time(&starting_time);
        m(l, cmpint, 20000000, sizeof(Line), k);
        time(&end_time);
        fprintf(results, "%ld,", end_time - starting_time);
        printf("k = %d, sorting by int, time:\t%ld\n",k, end_time - starting_time);
        printf("Showing a couple data that has been stored:\n");
        for (int i = 0; i < 21; i++)
        {
            print_line(l[i]);
        }
         printf("\n\n");

        //Sorting by Field3
        //copy_lines(lines, l);
        time(&starting_time);
        m(l, cmpfloat, 20000000, sizeof(Line), k);
        time(&end_time);
        fprintf(results, "%ld\n", end_time - starting_time);
        printf("k = %d, sorting by float, time:\t%ld\n",k, end_time - starting_time);
        printf("Showing a couple data that has been stored:\n");
        for (int i = 0; i < 21; i++)
        {
            print_line(l[i]);
        }
         printf("\n\n");


        simulation_end = time(&simulation_end);
        if(simulation_end - simulation_start >= (maxTime * 60))
        {
            printf("%d minutes have passed...\nInterrupting the simulations, results can be found in results.csv\n", maxTime);
            free(lines);
            free(l);
            fclose(file);
            fclose(results);
            return 0;
        }
    }
    

    free(lines);
    free(l);
    fclose(file);
    fclose(results);
}

void print_line(Line l)
{
    printf("id: %ld\t Word: %s\t\t int: %d\t float: %2f\n", l.id, l.c, l.n, l.f);
}
void copy_lines(Line* lines, Line* ret)
{
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
}