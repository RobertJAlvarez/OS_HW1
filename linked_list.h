#ifndef _LINKED_LIST_
#define _LINKED_LIST_

typedef struct s_Line {
  char *str;
  size_t length;
  struct s_Line *next;
} Line;

typedef struct s_List {
  int n_Lines;
  int max_Lines;
  struct s_Line *head;
  struct s_Line *tail;
} List;

/* Initialize the linked list to keep the history. */
List *init_LL(int k);

/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store */
void add_line(List *list, char *str, size_t length);

/*Print the entire contents of the list. */
void print_lines(List *list);

/*Free the history list and the strings it references. */
void free_history(List *list);

#endif
