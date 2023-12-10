#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd = 0;
    fd = open("test.txt", fd);
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
    printf("%s", get_next_line(fd));
/*     get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd); */
    close(fd);

    return (0);
}