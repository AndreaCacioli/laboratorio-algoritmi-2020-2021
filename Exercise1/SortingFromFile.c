#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "mbi.h"


char file_input[30] = "./records.csv";
char file_output[30] = "./results.csv";
int time_limit = 10;
int k_start = 0;
int step = 1;
int n = 20000000;

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

/*
    * A function that parses potential flags when launching the program
    * -h: shows help
    * -i: allows the user to choose the file to read from (default records.csv)
    * -o: allows the user to choose a neme for the file containing the time results (default results.csv) 
    * -t: allows the user to specify a time limit in minutes (default 10)
    * -k: allows the user to set a starting value of k (default 0)
    * -s or --step: allows the user to choose the increment of k for each step (default 1) 
    * -n: allows the user to specify the number of records (default 20000000)
*/
void parse_flags(int argc, char** args)
{
    for(int i = 1; i < argc; i++)
    {
        if(argc == 1)
        {
            printf("Running on default options...\nUse -h for more info\n");
            return;
        } 
        if(strcmp(args[i],"-h") == 0)
        {
            printf("\t* -h: shows help\n\t* -i: allows the user to choose the file to read from (default records.csv)\n\t* -o: allows the user to choose a neme for the file containing the time results (default results.csv)\n\t* -t: allows the user to specify a time limit in minutes (default 10)\n\t* -k: allows the user to set a starting value of k (default 0)\n\t* -s or --step: allows the user to choose the increment of k for each step (default 1)\n\t* -n: allows the user to specify the number of records (default 20000000)\n");
            exit(0);
        }
        if(strcmp(args[i],"-i") == 0)
        {
            strcpy(file_input,args[++i]);
            printf("Using %s as input file\n", file_input);
        }
        else if(strcmp(args[i],"-o") == 0)
        {
            strcpy(file_output,args[++i]);
            printf("Using %s as output file\n", file_output);
        }
        else if(strcmp(args[i],"-t") == 0)
        {
            time_limit = atoi(args[++i]);
            printf("Using %d as time limit\n", time_limit);
        }
        else if(strcmp(args[i],"-k") == 0)
        {
            k_start = atoi(args[++i]);
            printf("Using %d as k first value\n", k_start);
        }
        else if(strcmp(args[i],"-s") == 0 || strcmp(args[i], "--step") == 0)
        {
            step = atoi(args[++i]);
            printf("Using %d as k step\n", step);
        }
        else if(strcmp(args[i],"-n") == 0)
        {
            n = atoi(args[++i]);
            printf("Using %d as number of records\n", n);
        }
        else
        {
            printf("Error: check your parameters and retry\nA list of all possible parameters is found using -h as a flag\n");
        }
    }
}

int main(int argc, char** args)
{

    parse_flags(argc, args);

    FILE* file;
    FILE* results = fopen(file_output, "w");
    Line* l = (Line*)malloc(n * sizeof(Line));
    int i = 0;

    if((file = fopen(file_input, "r")) == NULL)
    {
        fprintf(stderr, "Could not open input file\n");
        return 1;
    }
    printf("File found!\n");

    Line* lines = malloc(n * sizeof(Line));
    
    printf("Populating the array...\n");
    while(!feof(file))
    {
        fscanf(file,"%ld,", &lines[i].id);

        lines[i].c = (char*)malloc(30);

        //lettura del file carattere dopo carattere
        for(int j = 0; j < 30; j++)
        {
            char character = ' ';
            fscanf(file,"%c", &character);
            if(character == ',') break;
            else lines[i].c[j] = character;
        }

        fscanf(file,"%d,%f", &lines[i].n, &lines[i].f);
        fflush(stdout);
        printf("\r%3.2f %%", (float)i/n * 100);
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

    for (int k = k_start; simulation_end - simulation_start < (time_limit * 60); k += step)
    {
        printf("Starting to sort for k = %d\n", k);
        time_t starting_time = 0;
        time_t end_time = 0;
        copy_lines(lines, l);

        //Sorting by Field1
        time(&starting_time);
        m(l, cmpstr, n, sizeof(Line), k);
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
        m(l, cmpint, n, sizeof(Line), k);
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
        m(l, cmpfloat, n, sizeof(Line), k);
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
    }
    
    printf("The time for the simulation has expired\n");
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
    for(int i = 0; i < n; i++)
    {
        ret[i].id = lines[i].id;
        ret[i].c = lines[i].c;
        ret[i].n = lines[i].n;
        ret[i].f = lines[i].f;
        fflush(stdout);
        printf("\rCopying data: %3.2f%%",(float)i/n * 100);
    }
    printf("\r");
}