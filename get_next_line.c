/*
 * read and how it works and why it remembers where it last stops
 * static variables
 * start by reading from a file
 * look for \n
 * there must be a condition which frees cache when the job is done
    i think that should be when i hit end of file
*/

#include "get_next_line.h"

char *ret_ln(char *cache)
{
	char	*line;
	int		c_len;
	int		i;

	if (!cache)
		return (NULL);
	i = 0;
	while (cache[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_memcpy(line, cache, i);
	return (line);
}

char *get_next_line(int fd)
{
	int			bytes;
    char 		*buffer;
    static char	*cache;
	char		*line;

    buffer = malloc(sizeof(char) * BUFFERSIZE + 1UL);
    if (!buffer)
        return (NULL);
    bytes = 1;
    while (bytes > 0)
    {
        bytes = read(fd, buffer, BUFFERSIZE);
		buffer[bytes] = 0;
        if (bytes == 0)
            return (buffer);
        if (bytes < 0)
            return (free(buffer), buffer = NULL, NULL);
        if (is_newline(buffer))
            break;
		printf("%s\n", buffer);
		cache = ft_strjoin(cache, buffer);
    }
	// filter the value of cache before returning it
	// return line
	line = ret_ln(cache);
	if (!line)
		return (free(buffer), free(cache), NULL);
	// now reset the value of cache
	return (line);
}

int main(void)
{
    int fd = open("test.txt", O_RDWR);

	//get_next_line(fd);
    char *line = get_next_line(fd);
    int ln = ft_strlen(line);

    write_to_fd(0, line, ln);
    write_to_fd(0, "\n", 1);

    close(fd);
    free(line);

    return 0;
}
