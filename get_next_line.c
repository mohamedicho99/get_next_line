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
 *
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
	int			bytes;
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
        if (bytes == 0)
            return (buffer);
		// cache gets overwritten here?
		// do i need to free it again inside ft_strjoin
		// i don't have to free buffer now because i still
		// have its address
		cache = ft_strjoin(cache, buffer);
        if (is_newline(cache))
            break;
    }
	cache = reset_cache(cache, &buffer);
	if (!cache)
		return (free(buffer), buffer = NULL, free(cache), cache = NULL, NULL);
	return (buffer);
}

int main(void)
{
    int fd = open("test.txt", O_RDWR);
    //int fd = open("ten.txt", O_RDWR);

    char *line;	
	int ln;
	while ((line = get_next_line(fd)) && ln != 0)
	{
		ln = ft_strlen(line);
		write_to_fd(0, line, ln);
		//printf("%d\n", ln);
	}

    close(fd);
    free(line);

    return 0;
}
