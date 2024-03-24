#include "roster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT_NAME_LEN 100 
int add_student(FILE* in, FILE* out, char* students[], int current_students, int const max_students){
    char *name_buffer = (char *)malloc(sizeof(char)*MAX_STUDENT_NAME_LEN);
    fscanf(in, "%99[^\n]\n",name_buffer);

    if(current_students == max_students){
        fprintf(out, "Command: add %s\n    Student %s not added. The class is already at capacity.\n", name_buffer,name_buffer);
        return current_students;
    }

    students[current_students] = name_buffer;
    fprintf(out, "Command: add %s\n    %s was added. %d spot(s) remain\n", name_buffer,name_buffer,max_students-current_students-1);
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
            fprintf(out, "Command: modify %s:%s\n    %s name modified to %s.\n", old_name_buffer,new_name_buffer,old_name_buffer,new_name_buffer);
            free(old_name_buffer);
            return;
        }
    }
    //Case 2 the student was not found
    fprintf(out,"Command: modify %s:%s\n    No student with name %s found.\n", old_name_buffer,new_name_buffer,old_name_buffer);
    free(old_name_buffer);
    free(new_name_buffer);
}

int remove_student(FILE* in, FILE* out, char* students[], int current_students, int const max_students){
    char *name_buffer = (char *)malloc(sizeof(char)*MAX_STUDENT_NAME_LEN);
    fscanf(in, "%99[^\n]\n",name_buffer);
    //Case 1 the student was found
    for(int i = 0; i< current_students;++i){
        if(strcmp(students[i],name_buffer)==0){
            free(students[i]);
            for(int j = i ; j<current_students-1;++j){
                students[j] = students[j+1];
            }
            //Setting last student to null
            students[--current_students] = NULL;
            
            fprintf(out, "Command: remove %s\n    Student %s removed. The course now has %d seats remaining.\n", name_buffer,name_buffer,max_students-current_students);
            free(name_buffer);
            return current_students;
        }
    }
    // //Case 2 the student was not found 
    // Command: remove Siwei Cao
    // No student named Siwei Cao was found to remove.
    fprintf(out,"Command: remove %s\n    No student named %s was found to remove.\n", name_buffer,name_buffer);
    free(name_buffer);
    return current_students;
}






int main(void){
    FILE* in = fopen("input.txt", "r");
    FILE* out = fopen("output.txt", "w");

    int max_students = 1;
    fscanf(in, "%d\n", &max_students);
    char** students = (char**)malloc(max_students * sizeof(char*));
    int current_students = 0;

    current_students = add_student(in, out, students, current_students, max_students);
    printf("\n %s \n",students[0]);
    modify_name(in, out, students, current_students);
        printf("\n %s \n",students[0]);

    fclose(in);
    fclose(out);
    free(students);
    return 0;
}