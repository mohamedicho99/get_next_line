/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-mo <mohel-mo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 22:35:36 by mohel-mo          #+#    #+#             */
/*   Updated: 2025/01/10 08:49:53 by mohel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*reset_cache(char **cache)
{
	char	*ptr;
	char	*line;
	char	*tmp;
	size_t	ptr_l;

	ptr = ft_strchr(*cache, '\n');
	if (!ptr)
		return (free(*cache), *cache = NULL, NULL);
	ptr++;
	ptr_l = (ptr - *cache) + 1;
	line = malloc(ptr_l * sizeof(char));
	if (!line)
		return (free(*cache), *cache = NULL, NULL);
	ft_strlcpy(line, *cache, ptr_l);
	tmp = ft_strdup(ptr);
	if (!tmp)
		return (free(line), line = NULL, free(*cache), cache = NULL, NULL);
	free(*cache);
	return (*cache = tmp, line);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*n_str;
	size_t	s1_len;
	size_t	s2_len;

	if ((!s1 || s1[0] == '\0') && (!s2 || s2[0] == '\0'))
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	n_str = malloc(s1_len + s2_len + 1 * sizeof(char));
	if (!n_str)
		return (NULL);
	ft_strlcpy(n_str, s1, s1_len + 1);
	ft_strlcpy(n_str + s1_len, s2, s2_len + 1);
	free(s1);
	return (n_str);
}

ssize_t	read_file(int fd, char **cache)
{
	char	*buffer;
	ssize_t	bytes;

	if (BUFFER_SIZE <= 0)
		return (0);
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (0);
	bytes = 1;
	while (bytes)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(*cache), *cache = NULL, bytes);
		buffer[bytes] = 0;
		if (bytes == 0)
			break ;
		*cache = ft_strjoin(*cache, buffer);
		if (!*cache)
			return (free(buffer), free(*cache), *cache = NULL, bytes);
		if (ft_strchr(*cache, '\n'))
			break ;
	}
	return (free(buffer), bytes);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*cache;
	ssize_t			read_status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_status = read_file(fd, &cache);
	if (read_status < 0 && cache)
		return (free(cache), cache = NULL, NULL);
	if (cache)
	{
		line = reset_cache(&cache);
		if (!line)
			return (NULL);
		return (line);
	}
	return (NULL);
}
