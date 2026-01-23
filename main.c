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
	main_init(gen, argv[1]);
	printf("\n==All right from here==\n");
	start_window(gen);
	
	return (0);
}
