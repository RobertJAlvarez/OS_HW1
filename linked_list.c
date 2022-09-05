#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "linked_list.h"
#include "my_c.h"

/* Initialize the linked list to keep the history. */
List *init_LL(int k)
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
void add_item(List *list, char *str, size_t length)
{
  Item *new = malloc(sizeof(Item));
  
  if (list->head == NULL) {   //If list is empty
    list->n_Lines = 1;
    list->head = new;
    list->tail = new;
  } else {
    list->tail->next = new;         //Add a line after tail
    list->tail = list->tail->next;  //Move tail one up
    ++list->n_Lines;                //Line was added
    if (list->n_Lines > list->max_Lines) //We pass the limit of line
      move_head(list);  //Move head one up and free space used by previous head
  }

  new->str = str;
  new->length = length;
  new->next = NULL;
  return;
}

/*Move head one up and free space used by previous head*/
void move_head(List *list)
{
  Item *temp = list->head;      //Save previous head

  if (temp == NULL)             //List is empty
    return;
  else if (temp == list->tail)  //We would eliminate last element in list
    list->tail = temp->next;

  list->head = list->head->next;//Move head one up
  free_item(temp);              //Free space used by previous head
  --list->n_Lines;              //Line was removed
  return;
}

/*Print the entire contents of the list. */
void print_lines(List *list)
{
  Item *curr = list->head;
  while (curr != NULL) {
    if (my_write(1, curr->str, curr->length) < 0) {
      fprintf(stderr, "Error writting: %s\n", strerror(errno));
      break;
    }
    curr = curr->next;
  }
  return;
}

/*Free item space use in malloc. */
void free_item(Item *item)
{
  free(item->str);
  free(item);
}

/*Free history list. */
void free_history(List *list)
{
  if (list->head == NULL) {
    free(list);
    return;
  }
  Item *curr = list->head;
  Item *next;           //Dummy variable to hold Line after curr
  while (curr->next != NULL) {
    next = curr->next;  //Save next item so we can free curr space without losing next item
    free_item(curr);
    curr = next;
  }
  //Free the space used for the last Line
  free_item(curr);
  free(list);
  return;
}

