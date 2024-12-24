#include "get_next_line.h"

void	write_to_fd(int fd, char *buffer, int ln)
{
    write(fd, buffer, ln);
}

/* strlcpy
// strlcat
// use them to make a new strjoin

size_t	ft_strlcpy(const char *dst, const char *src, size_t size) 
{
	size_t	l_src;
	size_t	i;

	// what if one of them is there?
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

size_t	ft_strlcat(const char *dst, const char *src, size_t dstsize)
{
	size_t	l_src;
	size_t	d_len;
	size_t	i;
	size_t	j;

	j = 0;
	if (!dst || !src)
		return (0);
	l_src = ft_strlen(src);
	if (dstsize == 0)
		return (l_src);
	d_len = ft_strlen(dst);
	if (d_len >= dstsize)
		return (l_src + dstsize);
	i = d_len;
	while (src[j] && j < (dstsize - d_len - 1))
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (d_len + l_src);
}

char *ft_strjoin(const char *s1, const char *s2)
{
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	n_str = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!n_str)
		return (NULL);

	ft_strlcpy(n_str, s1, s1_len + 1);
	ft_strlcat(n_str, s2, s2_len + s1_len + 1);
	return (n_str);
}
*/

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

int	is_newline(const char *s)
{
    int	i;

    i = 0;
    if (!s)
        return (0);
    while (s[i])
    {
        if (s[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

char	*ft_strdup(const char *s)
{
	char	*dst;
	int		i;

	if (!s)
		return (NULL);
	dst = malloc(sizeof(char) * (ft_strlen(s) + 1));
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

void	ft_memcpy(char *dst, const char *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!dst || !src)
		return ;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	tl;
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (ft_strdup(s1));
	if (!s1)
		return (ft_strdup(s2));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tl = s1_len + s2_len + 1;
	str = malloc(sizeof(char) * (tl + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len + 1);
	free(s1);
	return (str);
}

// string alo\nhere
// string alo\n
// \nstuff
char	*reset_cache(char *cache, char **buffer)
{
	int		i;
	char	*temp;

	i = 0;
	while (cache[i] && cache[i] != '\n')     
		i++;
	if (cache[i] == '\n')
		i++;
	free(*buffer);
	*buffer = malloc(sizeof(char) * (i + 1));
	if (!*buffer)
		return (free(cache), NULL);
	ft_memcpy(*buffer, cache, i);
	temp = ft_strdup(cache + i);
	free(cache);
	if (!temp)
		return (free(*buffer), *buffer = NULL, NULL);
	return (temp);
}
