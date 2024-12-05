/*
 * read and how it works and why it remembers where it last stops
 * static variables
 * start by reading from a file
 * look for \n
 * there must be a condition which frees cache when the job is done
    i think that should be when i hit end of file
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#define BUFFERSIZE 10

char *get_next_line(int fd)
{
    char *buffer = NULL;

    buffer = malloc(sizeof(char) * BUFFERSIZE + 1UL);
    if (!buffer)
        return (NULL);
    
    read(fd, buffer, BUFFERSIZE);

    /*
    int bytes = 1;
    while (bytes > 0)
    {
        read(fd, buffer, BUFFERSIZE);
        // if read == 0 means end of file
        // if read == -1 it didnt work as expected
        // if read == '\n' reached new line
    }
    */
	return (buffer);
}

void *write_to_fd(int fd, char *buffer, int ln)
{
    write(fd, buffer, ln);
}

int ft_strlen(char *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int main(void)
{
    // use open to get a fd
    // give it to getnextline
    // just get one line
    // write it to stdin
    int fd = open("test.txt", O_RDWR);

    char *line = get_next_line(fd);
    int ln = ft_strlen(line);
    write_to_fd(0, line, ln);
    write_to_fd(0, "\n", 1);
    printf("%d\n", ft_strlen(line));

    close(fd);
    free(line);
    return 0;
}
