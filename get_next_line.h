#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

char	*get_next_line(int fd);
void	write_to_fd(int fd, char *buffer, int ln);
int		ft_strlen(const char *s);
int		is_newline(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ret_ln(char *cache);
void	ft_memcpy(char *dst, const char *src, size_t n);
char	*reset_cache(char **cache);
//char    *reset_cache(char *cache, char **buffer);
//void    reset_cache(char **cache, char **buffer);
//char	read_file(char **cache, char **buffer, int fd);

#endif
