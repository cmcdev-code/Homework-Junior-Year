#include <stdio.h>
#include <stdlib.h>
#include "comic.h"


struct Comic_List load(FILE * ptr){
    //Burn the  first line
    char buffer[200];
    fgets(buffer, 200, ptr);
    struct Comic_List comics;
    
    


}



int main(int argc, char* argv[]){

    FILE * ptr = fopen("small.csv", "r");
    //Burn the  first line
    char buffer[200];
    fgets(buffer, 200, ptr);
    

    parse_csv_data(ptr);
 


    return 0;
}