
#include "cub3d.h"

int map_parser(char *argv)
{
    char *line;
    char **map;
    int  count;
    int  fd;

    fd = 0;
    count = 0;
    fd = open(argv[1], O_RDONLY);
    line = get_next_line(fd);
    while (line)
    {
        while (!ft_strncmp(line, "\n", 1))
        {
            free(line);
            line = get_next_line(fd);
        }
        while(line)
        {
            count++;
            free(line);
            line = get_next_line(fd);
        }
    }
    return (0);
}
