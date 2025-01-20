/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-mo <mohel-mo@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 22:36:11 by mohel-mo          #+#    #+#             */
/*   Updated: 2025/01/11 12:13:59 by mohel-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	l_src;
	size_t	i;

	if (!src || !dst)
		return (0);
	l_src = ft_strlen(src);
	if (size == 0)
		return (l_src);
	i = 0;
	while (src[i] && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (l_src);
}

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (i);
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		i;

	if (!s)
		return (NULL);
	dst = malloc(ft_strlen(s) + 1 * sizeof(char));
	if (!dst)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ptr;
	unsigned char	cc;
	size_t			i;

	if (!s)
		return (NULL);
	ptr = (unsigned char *)s;
	cc = (unsigned char)c;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == cc)
			return ((char *)ptr + i);
		i++;
	}
	if (cc == '\0')
		return ((char *)ptr + i);
	return (NULL);
}
