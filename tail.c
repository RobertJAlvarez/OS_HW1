#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define BUFFER_LEN (4096)
/*
 * I HAVEN'T START ON THIS ONE, I JUST CLONE head.c
*/

int str_cmp(char *s1, char *s2);
int str_to_int(char *s);

int str_cmp(char *s1, char *s2)
{
  while (*s1) {
    if (*s1 != *s2) break;
    s1++;
    s2++;
  }
  return *s1 - *s2;
}

int str_to_int(char *s)
{
  int num = 0;
  for (char c = *s; (c >= '0' && c <= '9'); c = *++s )
    num = num*10 + c-48;
  return num;
}

/* Call write() until all bytes are wirtten or until
 * an error occurs. Returns 0 on success and -1 on failure
 */
int my_write(int fd, const char *buf, size_t bytes) {
  ssize_t bytes_to_be_written;
  ssize_t bytes_already_written = 0;
  ssize_t bytes_written_this_time;

  bytes_to_be_written = bytes;
  while (bytes_to_be_written > ((size_t) 0)) {
    bytes_written_this_time = write(fd, &buf[bytes_already_written], bytes_to_be_written);
    if (bytes_written_this_time < ((ssize_t) 0)) { //Error
      return -1;
    }
    bytes_to_be_written -= (size_t) bytes_written_this_time;
    bytes_already_written += (size_t) bytes_written_this_time;
  }
  return 0;
}

int main(int argc, char **argv) {
  char buffer[BUFFER_LEN];
  int k = 10;
  ssize_t read_res;   //Signed size
  size_t read_bytes;  //unsigned size

  //Find the value of k if -n was provided
  for (int i = 1; i < argc; i++)
    if (str_cmp(argv[i],"-n") == 0) {
      k = str_to_int(argv[++i]);
      break;
    }

  //We keep on reading until the file hits the end-of-file condition
  while (k--) {
    //Try to read into the buffer, up to sizeof(buffer) bytes
    read_res = read(0, buffer, sizeof(buffer));

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
    
    //We need to write all the read_bytes bytes from buffer to standard output
    if (my_write(1, buffer, read_bytes) < 0) {
      //Display the appropriate error message and die
      fprintf(stderr, "Error writting: %s\n", strerror(errno));
      return 1;
    }
  }

  return 0;
}
