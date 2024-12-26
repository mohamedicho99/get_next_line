#include "get_next_line.h"
#include <limits.h>

char	*read_file(int fd, char **cache)
{
	char	*buffer;
	ssize_t	bytes;

	bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1UL));
	if (!buffer)
		return (NULL);
    while (bytes > 0)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes == 0)
            free(buffer);
        if (bytes < 0)
            return (free(buffer), buffer = NULL, free(*cache), *cache = NULL, NULL);
		buffer[bytes] = '\0';
        if (is_newline(*cache))
		{
            printf("[1] strjoin\n");
			*cache = ft_strjoin(*cache, buffer);
            if (!*cache)
            {
                printf("{0} it's emptry asat....");
                return (NULL);
            }
            break;
		}
		*cache = ft_strjoin(*cache, buffer);
        if (!*cache)
        {
            printf("{1} it's emptry asat....\n");
            return (NULL);
        }
        if (bytes == 0)
            return (buffer);
    }
	return (buffer);
}

char *get_next_line(int fd)
{
    char			*buffer;
    static char		*cache;
	
    if (fd < 0 && BUFFER_SIZE <= INT_MAX)
        return (NULL);
	buffer = read_file(fd, &cache);
	if (!buffer)
		return (NULL);
    printf("cache |%s|\n", cache);
	cache = reset_cache(cache, &buffer);
    printf("cache -- > %p\n", &cache);
	if (!cache)
		return (free(buffer), buffer = NULL, NULL);
	return (buffer);
}

int main(void)
{
    int fd = open("empty.txt", O_RDWR);

    char *line = get_next_line(fd);	
	if (!line)
	{
		printf("error, exiting...\n");
		return 1;
	}
	printf("first line: %s", line);
    free(line);

/*
	line = get_next_line(fd);
	printf("second line: %s", line);
    free(line);

	line = get_next_line(fd);
	printf("third line: %s", line);
    free(line);

	line = get_next_line(fd);
	printf("fourth line: %s", line);
    free(line);
*/
    close(fd);

    return 0;
}
