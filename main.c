
#include "cub3d.h"

int main(int argc, char **argv)
{
    (void)argc;
    if (map_parser(argv[1]))
        return (1);
    return (0);
}
