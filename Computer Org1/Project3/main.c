#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comic.h"

#define TAX 0.05

// Function to load the data from a csv file will set the data in the list of
// comics The list of comics MUST be freed by the caller
void load(char *filename, struct Comic_List *comics, FILE *cmd_ptr) {
  FILE *ptr = fopen(filename, "r");
  // Burn the  first line

  char buffer[200];
  fgets(buffer, 200, ptr);
  int starting_number_of_comics = comics->count;

  while (!feof(ptr)) {
    struct Comic comic = parse_csv_data(ptr);
    add_comic(comics, comic);
  }
  fclose(ptr);

  fprintf(cmd_ptr, "Command: load %s\n\tNumber of comics: %d\n", filename,
          comics->count - starting_number_of_comics);
}

// Function to buy a comic from the list of comics and add it to the shopping
// cart The shopping cart MUST be freed by the caller as it creates a dynamic
// copy of the comics that is passed in
void buy_comic(struct Comic_List list_of_comics, int index,
               struct Comic_List *shopping_cart, FILE *ptr) {
  if (index > list_of_comics.count || index < 0) {
    fprintf(ptr, "Unable to buy comic #%d\n", index);
    return;
  }

  struct Comic comic = create_comic(
      list_of_comics.list[index].date, list_of_comics.list[index].code,
      list_of_comics.list[index].publisher, list_of_comics.list[index].title,
      list_of_comics.list[index].cost);
  add_comic(shopping_cart, comic);

  fprintf(ptr, "Command: buy %d\nComic #%d added to purchase list\n", index,
          index);
}

// Flag 1 means used in display command
// Flag 0 means used in checkout command
// Function that will display the list of comics
void display(struct Comic_List list_of_comics, int flag, FILE *ptr) {
  if (flag == 1) {
    fprintf(ptr, "Command: display\n");
  }

  if (list_of_comics.count == 0) {
    fprintf(ptr, "List is currently empty.\n");
    return;
  }
  for (int i = 0; i < list_of_comics.count; i++) {
    fprintf(ptr, "Comic Number: %d\n", i + 1);
    fprintf(ptr, "\tDate: %s\n", list_of_comics.list[i].date);
    fprintf(ptr, "\tCode: %s\n", list_of_comics.list[i].code);
    fprintf(ptr, "\tPublisher: %s\n", list_of_comics.list[i].publisher);
    fprintf(ptr, "\tTitle: %s\n", list_of_comics.list[i].title);
    fprintf(ptr, "\tCost: %s\n", list_of_comics.list[i].cost);
  }
}

// Function to checkout the shopping cart
void checkout(struct Comic_List shopping_cart, FILE *ptr) {
  fprintf(ptr, "Command: checkout\nComics in Purchase List\n");
  display(shopping_cart, 0, ptr);

  float total = 0.0f;
  for (int i = 0; i < shopping_cart.count; i++) {
    if (shopping_cart.list[i].cost[0] ==
        '$') {  // Checks to see if it is even a valid cost
      char cost[6] = {
          shopping_cart.list[i].cost[1], shopping_cart.list[i].cost[2],
          shopping_cart.list[i].cost[3], shopping_cart.list[i].cost[4],
          shopping_cart.list[i].cost[5], '\0'};
      total += atof(cost);
    }
  }
  fprintf(ptr, " Subtotal: $%.2f\n      Tax: $%.2f \n    Total: $%.2f\n", total,
          total * TAX, total * (1.0 + TAX));
}

// Function to save the list of comics to a file in the same format as the
// input file
void save(struct Comic_List list_of_comics, char *filename, FILE *cmd_ptr) {
  FILE *ptr = fopen(filename, "w");
  fprintf(ptr, "Date,Code,Publisher,Title,Cost\n");
  for (int i = 0; i < list_of_comics.count; i++) {
    fprintf(ptr, "%s,%s,%s,%s,%s\n", list_of_comics.list[i].date,
            list_of_comics.list[i].code, list_of_comics.list[i].publisher,
            list_of_comics.list[i].title, list_of_comics.list[i].cost);
  }
  fclose(ptr);
  fprintf(cmd_ptr, "Command: save %s\n", filename);
}

// Function to clear the list of comics and free the memory allocated for each
// comic will have the list of comics reinitialized using init_comic_list
// function
void clear(struct Comic_List *list_of_comics, FILE *ptr) {
  // Free the memory allocated for each comic in the list
  for (int i = 0; i < list_of_comics->count; i++) {
    clean_comic_data(&list_of_comics->list[i]);
  }

  // Free the memory allocated for the list itself
  free(list_of_comics->list);
  // Reinitialize the list
  *list_of_comics = init_comic_list();

  fprintf(ptr, "Command: clear\n");
}

// Function to find a comic in the list of comics if it is valid
void find(struct Comic_List list_of_comics, int index, FILE *ptr) {
  fprintf(ptr, "Command: find %d\n", index);
  if (index > list_of_comics.count || index < 0) {
    fprintf(ptr, "There is no comic at index #%d in the list.\n", index);
    return;
  }
  fprintf(ptr, "\tDate: %s\n", list_of_comics.list[index].date);
  fprintf(ptr, "\tCode: %s\n", list_of_comics.list[index].code);
  fprintf(ptr, "\tPublisher: %s\n", list_of_comics.list[index].publisher);
  fprintf(ptr, "\tTitle: %s\n", list_of_comics.list[index].title);
  fprintf(ptr, "\tCost: %s\n", list_of_comics.list[index].cost);
}

// Function to remove a comic from the list of comics will free the memory
// allocated for the comic
void remove_comic(struct Comic_List *list_of_comics, int index, FILE *ptr) {
  fprintf(ptr, "Command: remove %d\n", index);
  if (index > list_of_comics->count || index < 0) {
    fprintf(ptr, "Comic at index %d was not removed\n", index);
    return;
  }

  clean_comic_data(&list_of_comics->list[index]);
  for (int i = index; i < list_of_comics->count - 1; i++) {
    list_of_comics->list[i] = list_of_comics->list[i + 1];
  }
  list_of_comics->count--;
  fprintf(ptr, "Comic at index %d successfully removed\n", index);
}

// The main loop`
int main(int argc, char *argv[]) {
  // Have to do something with argc or compiler will complain
  if (argc != 3) {
    printf("Usage: %s <command> <filename>\n", argv[0]);
    return 1;
  }

  // Initialize the list of comics
  struct Comic_List list_of_comics = init_comic_list();
  struct Comic_List shopping_cart = init_comic_list();


  
  // Open the file ptr is list of commands and cmd_ptr is the output file
  // detailing the commands that were executed
  FILE *ptr = fopen(argv[1], "r");
  FILE *cmd_ptr = fopen(argv[2], "w");

  // Buffer to store the command and its arguments
  char buffer[200];

  while (!feof(ptr)) {
    // Read in the line from command file
    fscanf(ptr, "%[^\n]\n", buffer);
    // Tokenize the command
    char *cmd = strtok(buffer, " ");

    // Check the command and call the appropriate function uses strtok to get
    // the arguments Same thing for all types of commands
    if (strcmp(cmd, "load") == 0) {
      load(strtok(NULL, " "), &list_of_comics, cmd_ptr);
    } else if (strcmp(cmd, "buy") == 0) {
      buy_comic(list_of_comics, atoi(strtok(NULL, " ")), &shopping_cart,
                cmd_ptr);
    } else if (strcmp(cmd, "display") == 0) {
      display(list_of_comics, 1, cmd_ptr);
    } else if (strcmp(cmd, "checkout") == 0) {
      checkout(shopping_cart, cmd_ptr);
    } else if (strcmp(cmd, "save") == 0) {
      save(list_of_comics, strtok(NULL, " "), cmd_ptr);
    } else if (strcmp(cmd, "clear") == 0) {
      clear(&list_of_comics, cmd_ptr);
    } else if (strcmp(cmd, "find") == 0) {
      find(list_of_comics, atoi(strtok(NULL, " ")), cmd_ptr);
    } else if (strcmp(cmd, "remove") == 0) {
      remove_comic(&list_of_comics, atoi(strtok(NULL, " ")), cmd_ptr);
    }
  }
  // Close the files
  fclose(ptr);
  fclose(cmd_ptr);
  // Need to free the memory allocated for each comic in the list
  for (int i = 0; i < list_of_comics.count; i++) {
    clean_comic_data(&list_of_comics.list[i]);
  }
  // Free the memory allocated for the list itself
  free(list_of_comics.list);

  for (int i = 0; i < shopping_cart.count; i++) {
    clean_comic_data(&shopping_cart.list[i]);
  }
  free(shopping_cart.list);

  return 0;
}