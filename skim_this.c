#include "get_next_line.h"
#include <limits.h>

ssize_t	read_file(int fd, char **cache)
{
	char	*buffer;
	ssize_t	bytes;

	bytes = 1;
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1UL));
	if (!buffer)
		return (0);
    while (bytes > 0)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes <= 0)
            return (free(buffer), buffer = NULL, free(*cache), *cache = NULL, bytes);
		buffer[bytes] = '\0';
        if (is_newline(*cache))
		{
			*cache = ft_strjoin(*cache, buffer);
            if (!*cache)
				return (free(buffer), buffer = NULL, free(*cache), *cache = NULL, bytes);
            break;
		}
		*cache = ft_strjoin(*cache, buffer);
        if (!*cache)
			free(buffer);
    }
	free(buffer);
	return (bytes);
}

char *get_next_line(int fd)
{
    char			*buffer;
    static char		*cache;
	ssize_t			read_status;

    if (fd < 0 && BUFFER_SIZE <= INT_MAX)
        return (NULL);
	read_status = read_file(fd, &cache);
	if (read_status <= 0)
		return (free(cache), NULL);
	printf("[+] cache --> %s\n", cache);
	/*
	line = reset_cache(&cache);
	if (!cache)
		return (free(buffer), buffer = NULL, NULL);
	*/
	return (cache);
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
    //free(line);

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
