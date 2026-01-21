
#include "../headers/cub3d.h"

int	initial_parsing(int argc, char *argv[])
{
	int	fd;

	if (argc != 2)
	{
		write(2, "Error\n", 6);
		write(2, "Incorrect number of arguments\n", 31);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\n", 6);
		write(2, argv[1], ft_strlen(argv[1]));
		if (errno == ENOENT)
			return (write(2, " does not exist\n", 17), 1);
		else if (errno == EACCES)
			return (write(2, " has no reading permissions\n", 29), 1);
	}
	return (close(fd), 0);
}
