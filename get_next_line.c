/*
 * read and how it works and why it remembers where it last stops
 * static variables
 * start by reading from a file
 * look for \n
 * there must be a condition which frees cache when the job is done
    i think that should be when i hit end of file
*/

#include "get_next_line.h"

char *ft_strdup(const char *s)
{
    if (!s)
        return (NULL);
    char *dst = malloc(sizeof(char) * (ft_strlen(s) + 1));
    if (!dst)
        return (NULL);
    int i = 0;
    while (s[i])
    {
        dst[i] = s[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

void    ft_memcpy(char *dst, const char *src, size_t n)
{
    unsigned char *d = (unsigned char *)dst;
    unsigned char *s = (unsigned char *)src;
    size_t i = 0;
    while (i < n)
    {
        d[i] = s[i];
        i++;
    }
    d[i] = '\0';
}

char    *ft_strjoin(const char *s1, const char *s2)
{
    int     tl;
    char    *str;
    size_t  s1_len;
    size_t  s2_len;

    if (!s1 && !s2)
        return (NULL);
    if (!s1)
        return (ft_strdup(s2));
    if (!s2)
        return (ft_strdup(s1));
    s1_len = ft_strlen(s1);
    s2_len = ft_strlen(s2);
    tl = s1_len + s2_len + 1;
    str = malloc(sizeof(char) * tl);
    if (!str)
        return (NULL);
    ft_memcpy(str, s1, s1_len);
    ft_memcpy(str + s1_len, s2, s2_len + 1);
    return (str);
}

char *get_next_line(int fd)
{
    char *buffer = NULL;
    static char *cache = NULL;

    buffer = malloc(sizeof(char) * BUFFERSIZE + 1UL);
    if (!buffer)
        return (NULL);
    
    int bytes = 1;
    while (bytes > 0)
    {
        bytes = read(fd, buffer, BUFFERSIZE);
        if (bytes == 0)
            return (buffer);
        if (bytes < 0)
            return (free(buffer), buffer = NULL, NULL);
        if(is_newline(buffer))
            break;
        // call strjoin with cash and buffer
        ft_strjoin(cache, buffer);
    }
    // call reset cash with cash and free buffer
	return (buffer);
}

int main()
{
    char fn[] = "mohamed";
    char ln[] = "el moudden";

    char *r = ft_strjoin(fn, ln);
    if (!r)
    {
        printf("it's not working\n");
        return (0);
    }
    printf("%s\n", r);
    free(r);

    return 0;
}

/*
int main(void)
{
    int fd = open("test.txt", O_RDWR);

    char *line = get_next_line(fd);
    int ln = ft_strlen(line);

    write_to_fd(0, line, ln);
    write_to_fd(0, "\n", 1);

    close(fd);
    free(line);

    return 0;
}*/
