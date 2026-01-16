
#include "cub3d.h"

int main(int argc, char **argv)
{
    static t_parsing data;

    (void)argc;
    if (map_parser(&data, argv[1]))
        return (1);
    return (0);
}
