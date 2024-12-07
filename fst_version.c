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

int ft_strlen(char *str)
{
    if (!str)
        return (0);
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

int is_newline(const char *s)
{
    if (!s)
        return (0);
    int i = 0;
    while (s[i])
    {
        if (s[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}

char *get_next_line(int fd)
{
    char *buffer = NULL;

    buffer = malloc(sizeof(char) * BUFFERSIZE + 1UL);
    if (!buffer)
        return (NULL);
    
    int bytes = 1;
    int tr = 0; // as in tracker
    while (bytes > 0)
    {
        printf("tracker at the start of the loop: %d\n", tr);
        bytes = read(fd, buffer, BUFFERSIZE);
        printf("bytes: %d\n", bytes);
        if (bytes == 0)
        {
            printf("tracker when bytes == 0: %d\n", tr);
            return (buffer);
        }
        if (bytes < 0)
        {
            printf("tracker when bytes < 0: %d\n", tr);
            return (free(buffer), buffer = NULL, NULL);
        }
        if(is_newline(buffer))
        {
            printf("tracker when new line is found in buffer: %d\n", tr);
            break;
        }
        tr++;
    }
    //printf("tracker after loop: %d\n", tr);

	return (buffer);
}

void *write_to_fd(int fd, char *buffer, int ln)
{
    write(fd, buffer, ln);
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
    printf("length of the line after first get_next_line call: %d\n", ln);
    write_to_fd(0, line, ln);
    write_to_fd(0, "\n", 1);

    close(fd);
    free(line);
    return 0;
}
