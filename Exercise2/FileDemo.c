#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "edit.h"

#define DICTIONARY_SIZE 661562
#define INT_MAX 2147483647

void draw_fancy_progress_bar(int i);

int main(int argc, char* args[])
{
    char** dictionary = malloc(DICTIONARY_SIZE * sizeof(char*));
    FILE* dictionary_file = fopen("dictionary.txt", "r");
    int word_sizes[DICTIONARY_SIZE];
    int edit_distances[DICTIONARY_SIZE];

    if(dictionary_file == NULL)
    {
        fprintf(stderr, "Could not open the dictionary file =(\n");
        return 1;
    }

    printf("Populating the dictionary...\n\n");
    for(int i = 0; i < DICTIONARY_SIZE; i++)
    {
        dictionary[i] = malloc(100 * sizeof(char));
        fgets(dictionary[i], 100, dictionary_file);
        int k = 0;
        while(dictionary[i][k] != '\n') k++;
        dictionary[i][k] = 0; //Removing final \n from each string
        word_sizes[i] = k;

        draw_fancy_progress_bar(i);        
    }

    printf("\n\n");

    FILE* input = fopen("correctme.txt", "r");

    if(input == NULL)
    {
        fprintf(stderr,"Could not find file correctme.txt\n");
        return 1;
    }

    while(!feof(input))
    {
        char* c = malloc(100);
        fscanf(input, "%s", c);
        int size = strlen(c); 

        for(int i = 0; i < size; i++)
        {
            c[i] = tolower(c[i]);
        }
        

        for(int i = 0; i < DICTIONARY_SIZE; i++)
        {
            int** mat = setup_mat(size, word_sizes[i]);
            edit_distances[i] = edit_distance_dyn(c, dictionary[i], size, word_sizes[i], mat);
            free_mat(mat, size);
        }
        int min = INT_MAX;
        for(int i = 0; i < DICTIONARY_SIZE; i++)
        {
            if(edit_distances[i] < min) min = edit_distances[i];
        }
        for(int i = 0; i < size; i++)
        {
            c[i] = toupper(c[i]);
        }
        printf("You spelt %s, did you mean...\n", c);
        for(int i = 0; i < DICTIONARY_SIZE; i++)
        {
            if(edit_distances[i] == min) printf("\t%s\n", dictionary[i]);
        }
        printf("\n");
        free(c);
    }

    //CLEANUP
    for(int i = 0; i < DICTIONARY_SIZE; i++)
    {
        free(dictionary[i]);
    }
    free(dictionary);
    fclose(dictionary_file);
    fclose(input);
}

void draw_fancy_progress_bar(int i)
{
    fflush(stdout);
    printf("\r\t[");
    int progress = (float)i / DICTIONARY_SIZE * 30;
    for(int j = 0; j < progress; j++)
    {
        printf("#");
    }
    for(int j = progress; j < 29; j++)
    {
        printf(" ");
    }
    printf("]");
}
        