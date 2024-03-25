#include "roster.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENT_NAME_LEN 100 
//Function that attempts to add a student to the class
// in: is the input file which the name will be read in from 
// out: is the output file which will display a log of the function call and the update
// students: is the array of students in the class
// current_students: is the number of students currently in the class
// max_students: is the maximum number of students that can be in the class
// returns the number of students in the class after the function call
int add_student(FILE* in, FILE* out, char* students[], int current_students, int const max_students){
    char *name_buffer = (char *)malloc(sizeof(char)*MAX_STUDENT_NAME_LEN);
    fscanf(in, "%99[^\n]\n",name_buffer);

    if(current_students == max_students){
        fprintf(out, "Command: add %s\n        Student %s not added. The class is already at capacity.\n", name_buffer,name_buffer);
        return current_students;
    }

    students[current_students] = name_buffer;
    fprintf(out, "Command: add %s\n        %s was added. %d spot(s) remain.\n", name_buffer,name_buffer,max_students-current_students-1);
    return current_students+1;
}


//Function that attempts to modify the name of a student in the class
// in: is the input file which the old and new name will be read in from in the format old_name:new_name
// out: is the output file which will display a log of the function call and the update(if it did update)
// students: is the array of students in the class
// current_students: is the number of students currently in the class
void modify_name(FILE* in, FILE* out, char* students[], int current_students){
    char *old_name_buffer= (char *)malloc(sizeof(char)*MAX_STUDENT_NAME_LEN);
    char *new_name_buffer= (char *)malloc(sizeof(char)*MAX_STUDENT_NAME_LEN);
    fscanf(in,"%99[^:]:%99[^\n]\n",old_name_buffer,new_name_buffer);
    //Case 1 the student was found
    for(int i = 0; i < current_students;++i){
        if(strcmp(students[i],old_name_buffer) == 0){
            free(students[i]);
            students[i] = new_name_buffer;
            fprintf(out, "Command: modify %s:%s\n	Student %s name modified to %s.\n", old_name_buffer,new_name_buffer,old_name_buffer,new_name_buffer);
         free(old_name_buffer);
            return;
        }
    }
    //Case 2 the student was not found
    fprintf(out,"Command: modify %s:%s\n        No student with name %s found.\n", old_name_buffer,new_name_buffer,old_name_buffer);
    free(old_name_buffer);
    free(new_name_buffer);
}

//Function that attempts to remove a student from the class(will shift back all students after the removed student to fill the gap)
// in: is the input file which the name of the student to be removed will be read in from
// out: is the output file which will display a log of the function call and the update(if it did update)
// students: is the array of students in the class
// current_students: is the number of students currently in the class
// max_students: is the maximum number of students that can be in the class
// returns the number of students in the class after the function call
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
            
            fprintf(out, "Command: remove %s\n	Student %s removed. The course now has %d seats remaining.\n", name_buffer,name_buffer,max_students-current_students);
            free(name_buffer);
            return current_students;
        }
    }
    // //Case 2 the student was not found 
    fprintf(out,"Command: remove %s\n        No student named %s was found to remove.\n", name_buffer,name_buffer);
    free(name_buffer);
    return current_students;
}


/// Function that displays the current students in the class (in output file)
// out: will display the current students in the class here
// students: is the array of students in the class
// current_students: is the number of students currently in the class
void display_class(FILE* out, char* students[], int current_students){
    fprintf(out,"Command: display\n");
    fprintf(out,"        Currently Enrolled:\n");
    for(int i = 0; i < current_students;++i){
        fprintf(out,"		Student %d: %s\n",i+1,students[i]);
    }
}
//Function that will delete the class and free all memory allocated for the students
// out: will display the log of the function call
// students: is the array of students in the class
// current_students: is the number of students currently in the class (will be set equal to 0 after function call)
void delete_class(FILE* out, char* students[], int* current_students){
    fprintf(out,"Command: delete\n");
    for(int i = 0; i < *current_students;++i){
        fprintf(out,"        %s removed in class delete.\n",students[i]);
        free(students[i]);
    }
    fprintf(out,"        Class was restarted and reopened for enrollment.\n\n");
    *current_students = 0;
}

