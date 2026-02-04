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
       {return (1);}
	printf("\n==All right from here==\n");
	main_init(gen, argv[1]);
	start_window(gen, argv[1]);
	return (0);
}

// 88 in 1
// 136 in 1
// 0 in 0
// 0 in 0