#include "get_next_line.h"

void write_to_fd(int fd, char *buffer, int ln)
{
    write(fd, buffer, ln);
}

int ft_strlen(const char *s)
{
    int i;

    i = 0;
    if (!s)
        return (i);
    while (s[i])
        i++;
    return (i);
}

int is_newline(const char *s)
{
    int i;

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

void ft_memcpy(char *dst, const char *src, size_t n)
{
	unsigned char *d = (unsigned char *)dst;
	unsigned char *s = (unsigned char *)src;
	size_t i = 0;
	if (!dst || !src)
		return ;

	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		tl;
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tl = s1_len + s2_len + 1;
	str = malloc(sizeof(char) * (tl + 1));
	// this will cause 
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_len);
	ft_memcpy(str + s1_len, s2, s2_len + 1);
	return (str);
}
