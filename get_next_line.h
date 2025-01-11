/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-mo <mohel-mo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 22:36:04 by mohel-mo          #+#    #+#             */
/*   Updated: 2024/12/31 23:48:20 by mohel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

char	*get_next_line(int fd);
void	write_to_fd(int fd, char *buffer, int ln);
int		ft_strlen(const char *s);
int		is_newline(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ret_ln(char *cache);
void	ft_memcpy(char *dst, const char *src, size_t n);
char	*reset_cache(char **cache);
void	*ft_calloc(size_t n_el, size_t size);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strdup(const char *s);

#endif
