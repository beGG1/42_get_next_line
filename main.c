#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main()
{
    int fd;
    char *s;

    fd = open("a.txt", O_RDONLY | O_NONBLOCK);
	if (fd == -1)
		return (0);

    s = get_next_line(fd);
    printf("%s", s);
    s = get_next_line(fd);
    printf("%s", s);
    s = get_next_line(fd);
    printf("%s", s);
}