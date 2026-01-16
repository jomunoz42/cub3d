#include "cub3d.h"
#include <fcntl.h>

int	main(int argc, char *argv[])
{
	t_gen	*gen;

	gen = gen_stuff();
	if (initial_parsing(argc, argv) != 0)
		return (1);
	gen->parse = parsing_init();
	if (!gen->parse)
		return (printf("Error: error initializing parsing\n"), 1);
	if (!validate_textures_path(argv[1], gen->parse))
		return (super_duper_hiper_free(), 1);
	printf("\n==All right from here==\n");
	start_window();
	return (0);
}
