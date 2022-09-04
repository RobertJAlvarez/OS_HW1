#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "history.h"
#include "my_c.h"

/* Initialize the linked list to keep the history. */
List *init_history(int k)
{
  List *p = malloc(sizeof(List));
  p->n_Lines = 0;
  p->max_Lines = k;
  p->head = NULL;
  p->tail = NULL;
  return p;
}

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store */
void add_line(List *list, char *str, size_t length)
{
  Line *new = malloc(sizeof(Line));
  Line *temp = list->head;

  if (temp == NULL) {   //If list is empty
    list->n_Lines = 1;
    list->head = new;
    list->tail = new;
  } else if (list->n_Lines == list->max_Lines) {  //We are max out of line
    list->head = list->head->next;  //Move head one up
    list->tail->next = new;         //Add a line after tail
    list->tail = list->tail->next;  //Move tail one up
    //Free space used by old head
    free(temp->str);
    free(temp);
  } else {              //Keep adding lines
    ++list->n_Lines;
    list->tail->next = new;         //Add a line after tail
    list->tail = list->tail->next;  //Move tail one up
  }
  new->str = str;
  new->length = length;
  new->next = NULL;
  return;
}

/*Print the entire contents of the list. */
void print_lines(List *list)
{
  Line *curr = list->head;
  while (curr != NULL) {
    if (my_write(1, curr->str, curr->length) < 0) {
      fprintf(stderr, "Error writting: %s\n", strerror(errno));
      break;
    }
    curr = curr->next;
  }
  return;
}

/*Free the history list and the strings it references. */
void free_history(List *list)
{
  if (list->head == NULL) {
    free(list);
    return;
  }
  Line *curr = list->head;
  Line *next;           //Dummy variable to hold Line after curr
  while (curr->next != NULL) {
    next = curr->next;  //Save next item so we can free curr space without losing next item
    free(curr->str);
    free(curr);
    curr = next;
  }
  //Free the space used for the last Line
  free(curr->str);
  free(curr);
  free(list);
  return;
}

