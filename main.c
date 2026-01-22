#include "./headers/cub3d.h"

t_gen	*gen_stuff(void)
{
	static t_gen	general;

	return (&general);
}

int	main(int argc, char *argv[])
{
	t_gen	*gen;

	gen = gen_stuff();
    if (parser(gen, argc, argv))
        return (1);
	// if (!validate_textures_path(argv[1], gen->parse))
	// 	return (super_duper_hiper_free(), 1);
	// printf("\n==All right from here==\n");
	// printf("FILE DESCRIPTOR OF [%s] is: %d\n", argv[1], gen->parse->fd);
	// start_window();
	return (0);
}
