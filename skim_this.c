#include "get_next_line.h"

ssize_t	read_file(int fd, char **cache)
{
	char	*buffer;
	ssize_t	bytes;

	if (BUFFER_SIZE <= 0)
		return (0);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
    while ((bytes = read(fd, buffer, BUFFER_SIZE)))
    {
        if (bytes < 0)
			return (free(buffer), buffer = NULL, free(*cache), *cache = NULL, bytes);
		if (bytes == 0)
			break;
		*cache = ft_strjoin(*cache, buffer);
		if (!*cache)
			return (free(buffer), buffer = NULL, free(*cache), *cache = NULL, bytes);
        if (is_newline(*cache))
            break;
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
	// check this value out
	if (cache)
	{
		line = reset_cache(&cache);
		if (!line)
			return (NULL);
	}
	return (line);
}

int main(void)
{
    int fd = open("test.txt", O_RDWR);
	char *line;

	int num = 1;
	printf("_________________________\n");
	while ((line = get_next_line(fd)))
	{
		if (!line)
		{
			printf("{!} line was not allocated, exiting...\n");
			return 1;
		}
		printf("{+} Line %d: %s", num, line);
		free(line);
		num++;
		printf("_________________________\n");
	}
    close(fd);
    return 0;
}
