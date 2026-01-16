#include "cub3d.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	t_parsing *parsing;
    if (initial_parsing(argc, argv) != 0)
		return (1);
	parsing = parsing_init();
	if (!parsing)
		return (printf("Error: error initializing parsing\n"), 1);
	if (validate_textures_path(argv[1], parsing) == 0)
		return (1);
	printf("\n==All right from here==\n");
	return (0);
}
