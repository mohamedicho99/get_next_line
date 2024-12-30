#include "get_next_line.h"

void	write_to_fd(int fd, char *buffer, int ln)
{
    write(fd, buffer, ln);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	unsigned char	c;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	c = 0;
	while (i != n)
	{
		ptr[i] = c;
		i++;
	}
}

void	*ft_calloc(size_t n_el, size_t size)
{
	void	*space;
	size_t	t_len;

	t_len = n_el * size;
	if (!size || size < 0)
		return (NULL);
	if (size != 0 && t_len / size != n_el)
		return (NULL);
	space = malloc(t_len);
	if (!space)
		return (NULL);
	ft_bzero(space, t_len);
	return (space);
}

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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
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
	dst = ft_calloc(sizeof(char), ft_strlen(s) + 1);
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

char *ft_strjoin(char *s1, char *s2)
{
    char *n_str;
    size_t s1_len;
    size_t s2_len;

	if ((!s1 || s1[0] == '\0') && (!s2 || s2[0] == '\0'))
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	n_str = ft_calloc(sizeof(char), s1_len + s2_len + 1);
	if (!n_str)
		return (NULL);
	ft_strlcpy(n_str, s1, s1_len + 1);
	ft_strlcat(n_str, s2, s2_len + s1_len + 1);
    free(s1);
	return (n_str);
}

char *ft_strchr(const char *s, int c)
{
	unsigned char	*ptr;
	unsigned char	cc;
	size_t			i;

	ptr = (unsigned char*)s;
	cc = (unsigned char)c;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == cc)
			return ((char*)ptr + i);
		i++;
	}
	if (cc == '\0')
		return ((char*)ptr + i);
	return (NULL);
}

char	*reset_cache(char **cache)
{
	char	*ptr;
	char	*line;
	char	*tmp;
	size_t	ptr_l;

	ptr = ft_strchr(*cache, '\n');
	if (!ptr && !*cache)
		return (NULL);
	// what if *cache and !ptr
	//ptr = NULL;
	ptr++;
	if (!ptr && *cache)
	{
		// i don't think we ever entered this
		// but do more tests
		printf("{+} we hit it...");
		return (*cache);
	}
	ptr_l = (ptr - *cache) + 1;
	//line = ft_calloc(sizeof(char), ((ptr - *cache) + 1));
	line = ft_calloc(sizeof(char), ptr_l);
	if (!line)
		return (free(*cache), *cache = NULL, NULL);
	//ft_strlcpy(line, *cache, (ptr - *cache) + 1);
	ft_strlcpy(line, *cache, ptr_l);
	tmp = ft_strdup(ptr);
	if (!tmp)
		return (free(line), line = NULL, free(*cache), cache = NULL, NULL);
	free(*cache);
	return (*cache = tmp, line);
}
