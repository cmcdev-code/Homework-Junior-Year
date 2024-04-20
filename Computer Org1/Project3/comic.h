#include <stdio.h>

struct Comic
{
    char* date;
    char* code;
    char* publisher;
    char* title;
    char *cost;
};

struct Comic_List
{
    struct Comic* list;
    int size;
    int count;
};

//Function returns a comic list with size 10 dynamically allocated
struct Comic_List init_comic_list();

//Function that will add the comic to the list of comics
void add_comic(struct Comic_List* comic_list, struct Comic comic);

//Function that will create a comic with the given arguments
// Must free the memory allocated for the comic
struct Comic create_comic(char* date, char* code, char* publisher, char* title, char* cost);

//Function will parse a single VALID line from a csv file
// Must check that the line is valid before calling this function
struct Comic  parse_csv_data(FILE * ptr);

//Function that will get rid of the memory allocated for the comic
void clean_comic_data(struct Comic* comic);