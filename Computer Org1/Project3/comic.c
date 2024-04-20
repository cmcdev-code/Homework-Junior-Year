#include "comic.h"
#include <string.h>
#include <stdlib.h>


struct Comic_List init_comic_list(){

    struct Comic_List comic_list;
    comic_list.size = 10;
    comic_list.count = 0;
    comic_list.list = (struct Comic *)malloc(comic_list.size * sizeof(struct Comic));
    return comic_list;
}

void clean_comic_data(struct Comic * comic){
    free(comic->code);
    free(comic->date);
    free(comic->publisher);
    free(comic->title);
    free(comic->cost);
}   

void add_comic(struct Comic_List* comic_list, struct Comic comic){
    //Check if the list is full
    if(comic_list->count == comic_list->size){
        //If the list is full, double the size of the list
        comic_list->size *= 2;
        comic_list->list = realloc(comic_list->list, comic_list->size * sizeof(struct Comic));
    }
    //Have to do a deep copy and free the memory allocated for the comic

    comic_list->list[comic_list->count] = comic;
    comic_list->count++;   
}

struct Comic create_comic(char* date, char* code, char* publisher, char* title, char* cost){
    struct Comic comic;    
    //Deep copy the strings
    comic.date = strdup(date);
    comic.code = strdup(code);
    comic.publisher = strdup(publisher);
    comic.title = strdup(title);
    comic.cost = strdup(cost);

    return comic;
}

struct Comic parse_csv_data(FILE * ptr){

    char date_buffer[100];
    char code_buffer[100];
    char publisher_buffer[100];
    char title_buffer[1000];
    char cost_buffer[10];


    fscanf(ptr, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", date_buffer, code_buffer, publisher_buffer, title_buffer, cost_buffer);
//reads in the data from the file and stores it in the buffers

//Allocate memory for the strings dynamically and copy the data from the buffer
char* date= (char *)calloc((strlen(date_buffer)+1),sizeof(char));

date = strncpy(date, date_buffer, strlen(date_buffer));

char * code = (char *)calloc((strlen(code_buffer)+1),sizeof(char));
code = strncpy(code, code_buffer, strlen(code_buffer));

char * publisher = (char *)calloc((strlen(publisher_buffer)+1),sizeof(char));
publisher = strncpy(publisher, publisher_buffer, strlen(publisher_buffer));

char * title = (char *)calloc((strlen(title_buffer)+1),sizeof(char));
title = strncpy(title, title_buffer, strlen(title_buffer));

char * cost = (char *)calloc((strlen(cost_buffer)+1),sizeof(char));
cost = strncpy(cost, cost_buffer, strlen(cost_buffer));

struct Comic comic = create_comic(date, code, publisher, title, cost);

//Free the memory allocated for the strings
free(date);
free(code);
free(publisher);
free(title);
free(cost);

return comic;

}