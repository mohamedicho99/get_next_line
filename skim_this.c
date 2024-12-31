#include "get_next_line.h"

ssize_t	read_file(int fd, char **cache)
{
	char	*buffer;
	ssize_t	bytes;

	if (BUFFER_SIZE <= 0)
		return (0);
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (0);
    while ((bytes = read(fd, buffer, BUFFER_SIZE)))
    {
        if (bytes < 0)
			return (free(buffer), buffer = NULL, free(*cache), *cache = NULL, bytes);
		buffer[bytes] = 0;
		if (bytes == 0)
			break;
		*cache = ft_strjoin(*cache, buffer);
		if (!*cache)
			return (free(buffer), buffer = NULL, free(*cache), *cache = NULL, bytes);
        if (ft_strchr(*cache, '\n'))
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
	if (cache)
	{
		line = reset_cache(&cache);
		if (!line)
			return (NULL);
		return (line);
	}
	return (NULL);
}

int main(void)
{
    int fd = open("ten.txt", O_RDWR);
	char *line;

	int num = 1;
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
	}
    close(fd);
    return 0;
}
