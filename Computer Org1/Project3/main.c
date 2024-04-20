#include <stdio.h>
#include <stdlib.h>
#include "comic.h"


struct Comic_List load(char* filename){
    FILE * ptr = fopen(filename, "r");
    //Burn the  first line

    char buffer[200];
    fgets(buffer, 200, ptr);
    struct Comic_List comics= init_comic_list();
    while(!feof(ptr)){
        struct Comic comic = parse_csv_data(ptr);
        add_comic(&comics, comic);
    }
    fclose(ptr);

    printf("Command: load %s\n\tNumber of comics:%d\n", filename, comics.count); 
    return comics;
}

void buy_comic(struct Comic_List list_of_comics, int index, struct Comic_List * bought_comics){
    
    struct Comic comic = list_of_comics.list[index-1];
    add_comic(bought_comics, comic);

    printf("Command: buy %d\nComic #%d added to purchase list\n", index,index);
}

void display(struct Comic_List list_of_comics){
    printf("Command: display\n");
    if(list_of_comics.count == 0){
        printf("List is currently empty.\n");
        return;
    }
    for(int i = 0; i < list_of_comics.count; i++){
        printf("Comic Number: %d\n", i+1);
        printf("\tDate: %s\n", list_of_comics.list[i].date);
        printf("\tCode: %s\n", list_of_comics.list[i].code);
        printf("\tPublisher: %s\n", list_of_comics.list[i].publisher);
        printf("\tTitle: %s\n", list_of_comics.list[i].title);
        printf("\tCost: %s\n", list_of_comics.list[i].cost);
    }

    
}

int main(int argc, char* argv[]){

    
    
    struct Comic_List comics = load(argv[2]);
    struct Comic_List bought_comics = init_comic_list();
    display(comics);
 
    return 0;
}