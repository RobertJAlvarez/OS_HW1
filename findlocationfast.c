#include <fcntl.h>    //open(), close()
#include <unistd.h>   //read(), lseek(), ssize_t
#include <stdio.h>    //fprintf(), stderr
#include <sys/mman.h> //mmap(), munmap()
#include <errno.h>    //errno
#include <string.h>   //strerror()
#include "my_c.h"     //my_write()

typedef struct {
 char number[6];
 char place[25];
 char newline;
} entry_t;

size_t str_len(char *s)
{
  char *c;
  for (c = s; *c != '\0'; c++);
  return ((size_t) (c - s));
}

void close_file(int fd, const char *filename)
{
  if (close(fd) < 0)
    fprintf(stderr, "Error closing file \"%s\": %s\n", filename, strerror(errno));
}

int only_digits(char *s)
{
  char count = 0;
  for (char c=*s; c >= '0' && c <= '9'; c=*++s, count++);
  return count == 6 ? 1 : 0;
}

int compare_entries(char *s1, char *s2)
{
  char *t1;
  char *t2;

  for (t1 = s1, t2 = s2; *t1 && (*t1 == *t2); t1++, t2++);

  if ((t1 - s1) == 6)
    return 0;
  return *t1 - *t2;
}

char *lookup_time(entry_t dict[], ssize_t num_entries, char *number)
{
  ssize_t l, r, m;
  int cmp;

  l = (ssize_t) 0;
  r = num_entries - ((ssize_t) 1);

  while (l <= r) {
    m = (l + r) / ((ssize_t) 2);
    cmp = compare_entries(dict[m].number, number);
    if (cmp == 0)
      return dict[m].place;

    if (cmp < 0)
      l = m + ((ssize_t) 1);
    else
      r = m - ((ssize_t) 1);
  }

  return NULL;
}

void print_trimmed(char *ptr)
{
  char *last_no_space;

  for (int i = 0; i < 25; i++) {
    if (ptr[i] != ' ')
      last_no_space = &ptr[i];
  }

  my_write(1, copy_str(ptr, (size_t) (last_no_space-ptr+1)), (size_t) (last_no_space-ptr+1));
}

int main(int argc, char **argv)
{
  char *filename;
  char *number;
  char *temp;
  int fd;
  char *ptr = NULL;
  off_t lseek_res;
  size_t file_size;
  char *place;

  //if first argument is not given or if first argument have anything that is not a number
  if ((argc < 3) || !only_digits(argv[2])) {
    temp = "Enter a North American phone number prefix with only the first 6 numbers.";
    my_write(1, temp, str_len(temp));
    return 1;
  }

  filename = argv[1];
  number = argv[2];

  fd = open(filename, O_RDONLY);
  
  if (fd < 0) {
    fprintf(stderr, "Error opening file \"%s\": %s\n", filename, strerror(errno));
    return 1;
  }

  lseek_res = lseek(fd, (off_t) 0, SEEK_END);

  if (lseek_res == (off_t) -1) {
    fprintf(stderr, "Error seeking in file \"%s\": %s\n", filename, strerror(errno));
    close_file(fd, filename);
    return 1;
  }

  file_size = (size_t) lseek_res;

  if ((file_size % sizeof(entry_t)) != ((size_t) 0)) {
    fprintf(stderr, "The file \"%s\" is not properly formatted.\n", filename);
    close_file(fd, filename);
    return 1;
  }

  ptr = mmap(NULL, file_size, PROT_READ, MAP_SHARED, fd, 0);

  close_file(fd, filename);

  if (ptr == MAP_FAILED) {
    fprintf(stderr, "Error mapping file \"%s\" in memory : %s\n", filename, strerror(errno));
    return 1;
  }

  //Find location of number on file
  place = lookup_time((entry_t *) ptr, ((ssize_t) (file_size / sizeof(entry_t))), number);

  //If line was not found, print error message and die
  if (place == NULL) {
    fprintf(stderr, "Code didn't match a North American phone number with prefix %s in nanpa.", number);
  } else {
    temp = "Place: ";
    my_write(1, temp, str_len(temp));
    print_trimmed(place);
    my_write(1, "\n", 2);
  }

  if (munmap(ptr, file_size) != 0) {
    fprintf(stderr, "Error unmapping file \"%s\" in memory : %s", filename, strerror(errno));
    return 1;
  }

  return 0;
}

