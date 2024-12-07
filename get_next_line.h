#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#define BUFFERSIZE 10

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char *get_next_line(int fd);
void write_to_fd(int fd, char *buffer, int ln);
int ft_strlen(const char *s);
int is_newline(const char *s);

#endif
