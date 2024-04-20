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

struct Comic_List init_comic_list();

void add_comic(struct Comic_List* comic_list, struct Comic comic);

struct Comic create_comic(char* date, char* code, char* publisher, char* title, char* cost);

//Function will parse a single VALID line from a csv file
// Must check that the line is valid before calling this function
struct Comic  parse_csv_data(FILE * ptr);


void clean_comic_data(struct Comic* comic);