#include "get_next_line.h"

char *get_next_line(int fd)
{
	ssize_t			bytes;
    char			*buffer;
	char 			*address_holder;
    static char		*cache;
	// or buffersize >= intmax
    if (fd < 0)
        return (NULL);

	// remove 1ul coz it should return a null
    buffer = malloc(sizeof(char) * BUFFER_SIZE + 1UL);
    if (!buffer)
        return (NULL);
    bytes = 1;
	int i = 0;
    while (bytes > 0)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes < 0)
            return (free(buffer), buffer = NULL, free(cache), cache = NULL, NULL);
		buffer[bytes] = 0;
        if (bytes == 0)
		{
			//free(cache);
			//printf("end of file reached, freed -> %p at %d turn\n", cache, i);
            return (buffer);
		}
        if (is_newline(cache))
		{
			printf("{+} found new line in cache at %d turn.\n", i);
            break;
		}
		cache = ft_strjoin(cache, buffer);
		printf("created in get_next_line -> %p at %d turn\n", cache, i);
		i++;
    }
	cache = reset_cache(cache, &buffer);
	if (!cache)
		return (free(buffer), buffer = NULL, NULL);
	return (buffer);
}

int main(void)
{
    int fd = open("test.txt", O_RDWR);

    char *line = get_next_line(fd);	
    //free(line);
	//line = get_next_line(fd);
	printf("here: %s", line);

	printf("freed at main! -> %p\n", line);
    free(line);
    close(fd);

    return 0;
}
