#include "get_next_line.h"

char *ret_ln(char *cache)
{
	char	*line;
	int		c_len;
	int		i;

	if (!cache)
		return (NULL);
	i = 0;
	while (cache[i] && cache[i] != '\n')
		i++;
	// we could of just used ft_strdup(cache + i) here, no??
	// instead of allocating and using memcpy
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
    if (fd < 0)
        return (NULL);

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
		cache = ft_strjoin(cache, buffer);
        if (is_newline(cache))
            break;
    }
	// this is wrong, it always prints that new line
	// every call to get next line re-initializes this cache variable to 
	// that first line
	/*line = ret_ln(cache);
	if (!line)
		return (free(buffer), free(cache), NULL);
	return (line);
	*/
	// create this function so, 
	// the gets what line originally gets, but set the cache to what's left
	// so give it the pointer to buffer (ask claude.ai) and change it 
	// inside the function...
	// the function returns the cash to be used in the next call to get next line
	cache = reset_cache(cache, buffer);
	if (!line)
		return (free(buffer), free(cache), NULL);
	return (buffer);
}

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
}

/* the while loop should exit with a break if new line is found in the cache
   another function called fix cache should kick in
   the function should return the line that we want up to the new line that was 
    found... and re-assign the rest to the cache variable itself (the static variable)

    so it should loop until new line and print 
    and check if the current char is new line and increments by 1 (aka i++)
    and then returns the cache + i as the new string!

    but be aware not to get a memory leak after doing so!
    because you may lose the origincal address of cache, thus you need to allocate a new string
    and return it!

steps:
    check if new line is found on cache and break from the while loop
*/


/*
 * read and how it works and why it remembers where it last stops
 * static variables
 * start by reading from a file
 * look for \n
 * there must be a condition which frees cache when the job is done
    i think that should be when i hit end of file
*/
