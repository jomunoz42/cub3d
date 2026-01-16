#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>

t_gen *gen_stuff()
{
	static t_gen	general;

	return (&general);
}

int start_window(void)
{
	t_gen *gen;

	gen = gen_stuff();
	if (mlx_data_init())
		return (1);
	gen->mlx_data->win_ptr = mlx_new_window(gen->mlx_data->mlx_ptr, 1600, 1000, "salve");
	if (!gen->mlx_data->win_ptr)
		return (1);
	mlx_key_hook(gen->mlx_data->win_ptr, handle_exit, NULL);
	mlx_loop(gen->mlx_data->mlx_ptr);
	return (0);
}
