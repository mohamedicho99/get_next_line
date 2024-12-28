#include "get_next_line.h"

ssize_t	read_file(int fd, char **cache)
{
	char	*buffer;
	ssize_t	bytes;

	bytes = 1;
	if (BUFFER_SIZE <= 0)
		return (0);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1UL));
	if (!buffer)
		return (0);
    while (bytes > 0)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes < 0)
			return (free(buffer), buffer = NULL, free(*cache), *cache = NULL, bytes);
		buffer[bytes] = '\0';
		if (bytes == 0 && ft_strlen(*cache))
			break;
		*cache = ft_strjoin(*cache, buffer);
        if (is_newline(*cache))
		{
			//*cache = ft_strjoin(*cache, buffer);
            if (!*cache)
				return (free(buffer), buffer = NULL, free(*cache), *cache = NULL, bytes);
            break;
		}
		//*cache = ft_strjoin(*cache, buffer);
    }
	return (free(buffer), bytes);
}

char *get_next_line(int fd)
{
	char			*line;
    static char		*cache;
	ssize_t			read_status;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
	read_status = read_file(fd, &cache);
	if (read_status <= 0)
		return (free(cache), NULL);
	line = reset_cache(&cache);
	if (!line)
		return (NULL);
	if (!ft_strlen(cache) && !read_status)
	{
		free(cache);
		cache = NULL;
	}

	return (line);
}

int main(void)
{
    int fd = open("ten.txt", O_RDWR);

    char *line = get_next_line(fd);	
	if (!line)
	{
		printf("{!} line was not allocated, exiting...\n");
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

	line = get_next_line(fd);
	printf("fifth line: %s", line);
    free(line);
*/

    close(fd);

    return 0;
}
