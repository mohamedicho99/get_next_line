#include "get_next_line.h"

/* TODO: read this and go through the code!
 * potential issues: what if cache was never dynamically allocated when
 * we hit bytes < 0
 * let's say read returns an error first thing? (how can we do that btw?)
 * cache only get's allocated when we hit ft_strjoin line
 * in read_file
 *
 * TODO:
 * what if strjoin didn't even succeed at doing anything?
 * any memory leaks there?
 * how can you test that?
 * */

/*
void	read_file(char **cache, char **buffer, int fd)
{
	int			bytes;

    *buffer = malloc(sizeof(char) * BUFFER_SIZE + 1UL);
    if (!*buffer)
        return ;
    bytes = 1;
    while (bytes > 0)
    {
        bytes = read(fd, *buffer, BUFFER_SIZE);
        if (bytes < 0)
		{
            free(*buffer);
			free(*cache);
 			*buffer = NULL;
 			*cache = NULL;
		}
		*buffer[bytes] = 0;
        if (bytes == 0)
            return ;
		*cache = ft_strjoin(*cache, *buffer);
        if (is_newline(*cache))
            break;
    }
}
char	*get_next_line(int fd)
{
    char 		*buffer;
    static char	*cache;

    if (fd < 0)
        return (NULL);

	read_file(&cache, &buffer, fd);
	if (!cache || !buffer)
		return (NULL);

	cache = reset_cache(cache, &buffer);
	if (!cache)
		return (free(buffer), buffer = NULL, free(cache), cache = NULL, NULL);
	return (buffer);
}
*/


char *get_next_line(int fd)
{
	ssize_t			bytes;
    char 		*buffer;
    static char	*cache;
    if (fd < 0)
        return (NULL);

    buffer = malloc(sizeof(char) * BUFFER_SIZE + 1UL);
    if (!buffer)
        return (NULL);
    bytes = 1;
    while (bytes > 0)
    {
        bytes = read(fd, buffer, BUFFER_SIZE);
        if (bytes < 0)
            return (free(buffer), buffer = NULL, free(cache), cache = NULL, NULL);
		buffer[bytes] = 0;
		// if bytes == 0
		// i should add a free(cache) here
		// because we've reached the end of file and thus no
		// need for it to be allocated anymore
        if (bytes == 0)
            return (buffer);
		cache = ft_strjoin(cache, buffer);
        if (is_newline(cache))
            break;
    }
	cache = reset_cache(cache, &buffer);
	if (!cache)
		return (free(buffer), buffer = NULL, NULL);
	//free(cache);
	// look more into why aren't we freeing cache here 
	// and why it works with valgrind and fsanitizer
	// check if this cache gets freed or not
	// check the last allocation it ever does
	// and if it gets freed then fine and use that in defence
	return (buffer);
}

int main(void)
{
    int fd = open("test.txt", O_RDWR);

	//get_next_line(fd);
    char *line = get_next_line(fd);	
	int ln = ft_strlen(line);
	printf("here: %s\n", line);
	/*
	while (line && ln != 0)
	{
		printf("it's working: %s\n", line);
		//write_to_fd(0, line, ln);
		
		free(line);
		line = get_next_line(fd);
		ln = ft_strlen(line);
	}*/

    close(fd);
	printf("%p\nfreed!\n", line);
    free(line);

    return 0;
}
