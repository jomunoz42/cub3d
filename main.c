#include "./headers/cub3d.h"
#include <fcntl.h>

t_gen	*gen_stuff(void)
{
	static t_gen	general;

	return (&general);
}

int	main(int argc, char *argv[])
{
	t_gen	*gen;

	gen = gen_stuff();
	if (initial_parsing(argc, argv) != 0)
		return (1);
    gen->parse = parsing_init();
    if (!gen->parse)
		return (printf("Error: error initializing parsing\n"), 1);
    if (map_parser(gen->parse, argv[1]))
            {return (1);}
	if (!ultimate_file_validation(argv[1], gen->parse))
		return (super_duper_hiper_free(), 1);
	printf("\n==All right from here==\n");
	printf("FILE DESCRIPTOR OF [%s] is: %d\n", argv[1], gen->parse->fd);
	start_window();
	return (0);
}
