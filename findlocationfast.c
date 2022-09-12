#include <fcntl.h>    //open(), close()
#include <unistd.h>   //read(), lseek(), ssize_t
#include <stdio.h>    //fprintf(), stderr
#include <sys/mman.h> //mmap(), munmap()
#include <errno.h>    //errno
#include <string.h>   //strerror()
#include "my_c.h"     //my_write()

int only_digits(char *s);
int only_digits(char *s)
{
  for (char c=*s; c >= '0' && c <= '9'; c=*++s);
  return *s == '\0' ? 1 : 0;
}

size_t trim_bytes(char *s);
size_t trim_bytes(char *s)
{
  //

  return 0;
}

size_t find_number(char *ptr, size_t low_line, size_t high_line);
size_t find_number(char *ptr, size_t low_line, size_t high_line)
{
  size_t n_line = 0;

  //

  return n_line;
}

void print_city(char *ptr)
{
  my_write(1,ptr,26*sizeof(char)-trim_bytes(ptr));
}

void my_unmap(char *ptr, size_t file_size);
void my_unmap(char *ptr, size_t file_size)
{
  if (munmap(ptr, file_size) != 0)
    printf("UnMapping failed\n");
}

int main(int argc, char **argv)
{
  const char *file = "nanpa";
  int fd;
  char *ptr = NULL;
  const size_t max_lines = 166482;
  const size_t file_size = max_lines*32;  //There are 32 bytes per line
  size_t at_line = (size_t) 0;
  size_t start_place = (size_t) 0;

  //if first argument is not given or if first argument have anything that is not a number
  if ((argc == 1) || !only_digits(argv[1])) {
    printf("Enter a North American phone number prefix with only the first 6 numbers.\n");
    return 1;
  }

  fd = open(file, O_RDONLY);
  ptr = mmap(NULL, file_size, PROT_READ, MAP_SHARED, fd, 0);

  close(fd);

  if (ptr == MAP_FAILED) {
    printf("Mapping Failed\n");
    return 1;
  }

  //Find location of number on file
  at_line = find_number(ptr,0,max_lines);

  //If line was not found, print error message and die
  if (at_line < 0) {
    printf("Code didn't match a North American phone number prefix in nanpa.");
    my_unmap(ptr, file_size);
    return 1;
  }

  //City start 6 characters after number does
  start_place = 32*at_line*sizeof(char) + 6*sizeof(char);

  //Output city and state where number belong to
  print_city(&ptr[start_place]);

  my_unmap(ptr, file_size);
  return 0;
}

