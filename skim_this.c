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
		printf("buffer: %s\n", buffer);
        if (bytes < 0)
            return (free(buffer), buffer = NULL, free(*cache), *cache = NULL, NULL);
		buffer[bytes] = 0;
        if (bytes == 0)
            return (buffer);
        if (is_newline(*cache))
		{
			printf("new line is found in cache, break, mov to cach_reset\n");
			printf("\n\ncache -> %s\n\n", *cache);
			*cache = ft_strjoin(*cache, buffer);
            break;
		}
		*cache = ft_strjoin(*cache, buffer);
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
	cache = reset_cache(cache, &buffer);
	if (!cache)
		return (free(buffer), buffer = NULL, NULL);
	return (buffer);
}

int main(void)
{
    int fd = open("test.txt", O_RDWR);

    char *line = get_next_line(fd);	
	printf("first line: %s\n", line);
    free(line);

	printf("\n\ncalling get_next_line again...\n\n");

	line = get_next_line(fd);
	printf("second line: %s\n", line);

    free(line);
    close(fd);

    return 0;
}
