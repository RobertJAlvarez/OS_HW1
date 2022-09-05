#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

//Compare two strings, return > 0 if s1 > s2, < 0 if s1 < s2, 0 if s1 == s2
int str_cmp(char *s1, char *s2)
{
  while (*s1 && (*s1 == *s2)) {
    s1++;
    s2++;
  }
  return *s1 - *s2;
}

int str_to_int(char *s)
{
  int num = 0;
  for (char c = *s; c >= '0' && c <= '9'; c = *++s)
    num = num*10 + c-48;
  return num;
}

/* Returns a freshly allocated new zero-terminated string containing <len> chars from <inStr> */
char *copy_str(char *inStr, size_t bytes)
{
  char *new_str = malloc(bytes+sizeof(char)); //1 extra because of '\0'
  if (new_str == NULL) return NULL; //Not enough space in malloc
  char *temp = new_str; //save starting position of the new string
  while ((bytes-sizeof(char)) && (*temp++ = *inStr++) != '\0');
  *temp = '\0';   //Set last character to '\0'
  return new_str;
}

/* Call write() until all bytes are written or until
 * an error occurs. Returns 0 on success and -1 on failure
 */
int my_write(int fd, const char *buf, size_t bytes)
{
  ssize_t bytes_to_be_written;
  ssize_t bytes_already_written = 0;
  ssize_t bytes_written_this_time;

  bytes_to_be_written = bytes;
  while (bytes_to_be_written > ((size_t) 0)) {
    bytes_written_this_time = write(fd, &buf[bytes_already_written], bytes_to_be_written);
    if (bytes_written_this_time < ((ssize_t) 0)) //Error
      return -1;
    bytes_to_be_written -= (size_t) bytes_written_this_time;
    bytes_already_written += (size_t) bytes_written_this_time;
  }
  return 0;
}

