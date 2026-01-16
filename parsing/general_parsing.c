#include "../cub3d.h"

int initial_parsing(int argc, char *argv[])
{
	if (argc != 2)
		return (printf("Error: incorrect arguments\n"), 1);
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return (printf("Error: [%s] file not found\n", argv[1]), 1);
    return (0);
}