#include "../cub3d.h"

int	initial_parsing(int argc, char *argv[])
{
	int	fd;

	if (argc != 2)
		return (printf("Error: incorrect arguments\n"), 1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (close(fd), printf("Error: [%s] file not found\n", argv[1]), 1);
	close(fd);
	return (0);
}
