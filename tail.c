#include <fcntl.h>      //open(), close()
#include <unistd.h>     //read()
#include <stdio.h>      //fprintf(), stderr
#include <errno.h>      //errno
#include <string.h>     //strerror()
#include "linked_list.h"
#include "my_c.h"

#define BUFFER_LEN (4096)

int main(int argc, char **argv)
{
  List *LL = NULL;
  char buffer[BUFFER_LEN];
  char *file = NULL;
  int k;
  ssize_t read_res;
  size_t remaining_bytes;
  size_t bytes_read;
  size_t line_bytes;
  int fd_r;

  k = 10;   //Assume there was no -n # provided
  //Find the value of k if -n was provided and save file names if any
  for (int i = 1; i < argc; i++) {
    if (str_cmp(argv[i],"-n") == 0) { // Check if the argument is -n
      if (++i >= argc) {  //If there is nothing after -n
        fprintf(stderr, "head: option requires an argument -- n\nusage: head [-n lines | -c bytes] [file ...]\n");
        return 1;
      }
      //Get what is after -n
      k = str_to_int(argv[i]);
      if (k == 0) { //If 0, a negative number or a non-number got input after -n
        fprintf(stderr, "head: illegal line count -- %s\n",argv[i]);
        return 1;
      }
    } else {
      file = argv[i];
    }
  }

  LL = init_LL(k);

  fd_r = 0; //Assume no file were given, input comes from keyboard
  //Get file descriptor if any
  if (file != NULL)
    fd_r = open(file, O_RDONLY);

  //We keep on reading until the file hits the end-of-file condition
  while (1) {
    //Try to read into the buffer, up to sizeof(buffer) bytes
    read_res = read(fd_r, buffer, sizeof(buffer));

    //Handle the return values of the read system call

    //If the returned value is zero, we are done, as this is end-of-file
    if (read_res == ((ssize_t) 0)) break;
    //If the returned value is negative, we have an error and we die
    if (read_res < ((ssize_t) 0)) {
      //Display the appropriate error message and die
      fprintf(stderr, "Error reading: %s\n", strerror(errno));
      return 1;
    }

    //Here we known that read_res in positive.
    remaining_bytes = (size_t) read_res;

    bytes_read = (size_t) 0;
    while (remaining_bytes > (size_t) 0) {
      line_bytes = get_line_bytes(&buffer[bytes_read], remaining_bytes);
      add_item(LL, copy_str(&buffer[bytes_read],line_bytes), line_bytes);
      remaining_bytes -= line_bytes;
      bytes_read += line_bytes;
    }
  }

  if (fd_r != 0)
    close(fd_r);

  print_lines(LL);

  return 0;
}

