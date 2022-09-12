#include <fcntl.h>    //open(), close()
#include <unistd.h>   //lseek()
#include <stdio.h>    //fprintf(), stderr
#include <sys/mman.h> //mmap(), munmap()

/*
#include <unistd.h> //read(), ssize_t
#include <errno.h>  //errno
#include <string.h> //strerror()
#include "my_c.h"
*/

//off_t lseek(int fildes, off_t offset, int whence);
//void *mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
//int munmap(void *addr, size_t len);

int only_digits(char *s);

int only_digits(char *s)
{
  for (char c=*s; c >= '0' && c <= '9'; c=*++s);
  return *s == '\0' ? 1 : 0;
}

int main(int argc, char **argv)
{
  char *file = "nanpa";
  int fd;

  //if first argument is not given or if first argument have anything that is not a number
  if ((argc == 1) || !only_digits(argv[1])) {
    printf("Enter a North American phone number prefix with only the first 6 numbers.\n");
    return 1;
  }

  fd = open(file, O_RDONLY);

  //Find location of number on file

  //If line was not found, print error message and die

  //Trim line

  //Delete number

  //Output city and state where number belong to

  close(fd);
  return 0;
}
