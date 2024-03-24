#include "roster.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_STUDENT_NAME_LEN 100 
int add_student(FILE* in, FILE* out, char* students[], int current_students, int const max_students){
    char *name_buffer = (char *)malloc(sizeof(char)*MAX_STUDENT_NAME_LEN);
    fscanf(in, "%99[^\n]\n",name_buffer);

    if(current_students == max_students){
        fprintf(out, "Command: add %s\n    Student %s not added. The class is already at capacity.\n", name_buffer,name_buffer);
        return current_students;
    }

    students[current_students] = name_buffer;
    fprintf(out, "Command: add %s\n    %s was added. %d spot(s) remain", name_buffer,name_buffer,max_students-current_students-1);
    return current_students+1;
}

void modify_name(FILE* in, FILE* out, char* students[], int current_students){
    char *old_name_buffer= (char *)malloc(sizeof(char)*MAX_STUDENT_NAME_LEN);
    char *new_name_buffer= (char *)malloc(sizeof(char)*MAX_STUDENT_NAME_LEN);
    fscanf(in,"%99[^:]:%99[^\n]\n",old_name_buffer,new_name_buffer);
    //Case 1 the student was found
    for(int i = 0; i < current_students;++i){
        if(strcmp(students[i],old_name_buffer) == 0){
            free(students[i]);
            students[i] = new_name_buffer;
            fprintf(out, "Command: modify %s:%s\n    %s name modified to %s.", old_name_buffer,new_name_buffer,old_name_buffer,new_name_buffer);
            free(old_name_buffer);
            return;
        }
    }
    //Case 2 the student was not found
    fprintf(out,"Command: modify %s:%s\n    No student with name %s found.", old_name_buffer,new_name_buffer,old_name_buffer);
    free(old_name_buffer);
    free(new_name_buffer);
}





int main(void){
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int max_students = 1;
    fscanf(in, "%d\n", &max_students);
    char** students = (char**)malloc(max_students * sizeof(char*));
    int current_students = 0;

    current_students = add_student(in, out, students, current_students, max_students);
    fclose(in);
    fclose(out);
    free(students);
    return 0;
}