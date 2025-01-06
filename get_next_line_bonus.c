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
			return (free(buffer), free(*cache), *cache = NULL, bytes);
		buffer[bytes] = 0;
		if (bytes == 0)
			break;
		*cache = ft_strjoin(*cache, buffer);
		if (!*cache)
			return (free(buffer), free(*cache), *cache = NULL, bytes);
        if (ft_strchr(*cache, '\n'))
            break;
    }
	return (free(buffer), bytes);
}

char	*get_next_line(int fd)
{
	char			*line;
    static char		*cache[1024];
	ssize_t			read_status;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
	read_status = read_file(fd, &cache[fd]);
	if (read_status < 0 && cache[fd])
		return (free(cache[fd]), cache[fd] = NULL, NULL);
	if (cache[fd])
	{
		line = reset_cache(&cache[fd]);
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
