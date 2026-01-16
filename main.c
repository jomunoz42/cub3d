#include "cub3d.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	t_parsing *parsing;
    if (parse(argc, argv, parsing) != 0)
		return (1);
	parsing = parsing_init();
	if (!parsing)
		return (printf("Error: error initializing parsing\n"), 1);
	get_texture_info(argv[1], parsing);
	return (0);
}
