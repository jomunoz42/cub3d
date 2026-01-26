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
	// for (int i = 0; i < 6; i++)
	// 	printf("right after parser: texture_info[%d]: %s\n", i, gen->parse->textures_info[i]);
	// if (!validate_textures_path(argv[1], gen->parse))
	// 	return (super_duper_hiper_free(), 1);
	// printf("\n==All right from here==\n");
	// printf("FILE DESCRIPTOR OF [%s] is: %d\n", argv[1], gen->parse->fd);
	main_init(gen, argv[1]);
	if (!gen->parse->textures_info)
		printf("nigga\n");
	else
		printf("BRUH\n");
	printf("TEXTURE INFO = %s", gen->parse->textures_info[0]);
	for (int i = 0; gen->parse->textures_info[i]; i++)
		printf("texture[%d] = %s\n", i, gen->parse->textures_info[i]);
	start_window(gen, argv[1]);
	return (0);
}
