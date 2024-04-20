#include <stdio.h>
#include <stdlib.h>
#include "comic.h"

#define TAX 0.05

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

void buy_comic(struct Comic_List list_of_comics, int index, struct Comic_List * shopping_cart){
    
    struct Comic comic = create_comic(list_of_comics.list[index-1].code, 
                                      list_of_comics.list[index-1].date, 
                                      list_of_comics.list[index-1].publisher, 
                                      list_of_comics.list[index-1].title, 
                                      list_of_comics.list[index-1].cost);
    add_comic(shopping_cart, comic);

    printf("Command: buy %d\nComic #%d added to purchase list\n", index,index);
}
//Flag 1 means used in display command
//Flag 0 means used in checkout command
void display(struct Comic_List list_of_comics, int flag){
    if(flag==1){
        printf("Command: display\n");
    }
    else{
        printf("Comics in Purchase List\n");
    }
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

void checkout(struct Comic_List shopping_cart){
    printf("Command: checkout\nComics in Purchase List\n");
    display(shopping_cart,0);
    float total = 0.0f;
    for(int i = 0; i < shopping_cart.count; i++){
        if(shopping_cart.list[i].cost[0] == '$'){
            char cost[6]={shopping_cart.list[i].cost[1],
                          shopping_cart.list[i].cost[2], 
                          shopping_cart.list[i].cost[3], 
                          shopping_cart.list[i].cost[4],
                          shopping_cart.list[i].cost[5], 
                          '\0'};
            total += atof(cost);
        }
    }
    printf(" Subtotal: $%.2f\n      Tax: $%.2f \n    Total: $%.2f\n", total, total*TAX, total*(1.0+TAX));

}

void save(struct Comic_List list_of_comics, char* filename){
    FILE * ptr = fopen(filename, "w");
    fprintf(ptr, "Date,Code,Publisher,Title,Cost\n");
    for(int i = 0; i < list_of_comics.count; i++){
        fprintf(ptr, "%s,%s,%s,%s,%s\n", list_of_comics.list[i].date, list_of_comics.list[i].code, list_of_comics.list[i].publisher, list_of_comics.list[i].title, list_of_comics.list[i].cost);
    }
    fclose(ptr);
    printf("Command: save %s\n\tNumber of comics:%d\n", filename, list_of_comics.count); 
}

void clear(struct Comic_List * list_of_comics){
    
    //Free the memory allocated for each comic in the list
    for(int i = 0; i < list_of_comics->count; i++){
        clean_comic_data(&list_of_comics->list[i]);
    }

    //Free the memory allocated for the list itself
    free(list_of_comics->list);
    //Reinitialize the list
    *list_of_comics   = init_comic_list();

    printf("Command: clear\n");
}


void find(struct Comic_List list_of_comics,int index){
    printf("Command: find %d\n", index);
    if(index  > list_of_comics.count){
        printf("There is no comic at index #%d in the list.\n", index);
        return;
    }
    printf("\tDate: %s\n", list_of_comics.list[index-1].date);
    printf("\tCode: %s\n", list_of_comics.list[index-1].code);
    printf("\tPublisher: %s\n", list_of_comics.list[index-1].publisher);
    printf("\tTitle: %s\n", list_of_comics.list[index-1].title);
    printf("\tCost: %s\n", list_of_comics.list[index-1].cost);
}

void remove_comic(struct Comic_List * list_of_comics, int index){
    printf("Command: remove %d\n", index);
    if(index -1 > list_of_comics->count){
        printf("Comic at index %d was not removed\n", index);
        return;
    }
    free(list_of_comics->list[index-1].code);
    free(list_of_comics->list[index-1].date);
    free(list_of_comics->list[index-1].publisher);
    free(list_of_comics->list[index-1].title);
    free(list_of_comics->list[index-1].cost);
    for(int i = index-1; i < list_of_comics->count-1; i++){
        list_of_comics->list[i] = list_of_comics->list[i+1];
    }
    list_of_comics->count--;
}

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("Usage: %s <command> <filename>\n", argv[0]);
        return 1;
    }
    
    
    struct Comic_List comics = load(argv[2]);
    struct Comic_List bought_comics = init_comic_list();
    buy_comic(comics, 1, &bought_comics);
    buy_comic(comics, 2, &bought_comics);
    buy_comic(comics, 3, &bought_comics);
 


    clear(&comics);
 
    checkout(bought_comics);

    save(bought_comics, "bought_comics.csv");
    


    return 0;
}