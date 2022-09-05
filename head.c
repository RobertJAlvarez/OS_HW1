#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "linked_list.h"
#include "my_c.h"

#define BUFFER_LEN (4096)

int main(int argc, char **argv) {
  char buffer[BUFFER_LEN];
  List *files = init_LL(argc-1);
  int k;
  int n_lines_printed;
  ssize_t read_res;   //Signed size
  size_t read_bytes;  //unsigned size
  int fd_r;

  k = 10;
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
      files->max_Lines -= 2; //Two arguments are -n and # so they cannot be files
    } else {
      add_item(files, argv[i], (size_t)sizeof(argv[i]));
    }
  }

  fd_r = 0; //No files were given, input comes from keyboard
  if (files->n_Lines != 0) {
    fd_r = open(files->head->str, O_RDONLY); //Files were provided
    move_head(files);
  }

//printf("%d\n",fd_r);
//printf("k = %d\n", k);
  //We keep on reading until the file hits the end-of-file condition
  n_lines_printed = 0;
  while (n_lines_printed++ < k) {
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
    read_bytes = (size_t) read_res;
//printf("buffer before my_write:\n%s\n",buffer);
    //We need to write all the read_bytes bytes from buffer to standard output
    if (my_write(1, buffer, read_bytes) < 0) {
      //Display the appropriate error message and die
      fprintf(stderr, "Error writting: %s\n", strerror(errno));
      return 1;
    }
//printf("n_lines_printed = %d\n", n_lines_printed);
  }

  if (fd_r != 0)
    close(fd_r);

  return 0;
}

