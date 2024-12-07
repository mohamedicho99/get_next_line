#include "get_next_line.h"

void write_to_fd(int fd, char *buffer, int ln)
{
    write(fd, buffer, ln);
}

int ft_strlen(const char *s)
{
    int i;

    i = 0;
    if (!s)
        return (i);
    while (s[i])
        i++;
    return (i);
}

int is_newline(const char *s)
{
    int i;

    i = 0;
    if (!s)
        return (0);
    while (s[i])
    {
        if (s[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}
