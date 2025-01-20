#include "get_next_line.h"

int main()
{
    char *line;
    int fd = open("icho", O_RDONLY);

    while ((line = get_next_line(fd)))
    {
        printf("line: %s", line);
        free(line);
    }
    close(fd);
}
