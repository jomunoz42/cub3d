#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>

t_gen	*gen_stuff(void)
{
	static t_gen	general;

	return (&general);
}

int put_arm(void *param)
{
	t_gen *gen;

	(void)param;
	gen = gen_stuff();
	if (!gen->arm)
		return (0);
	mlx_put_image_to_window( gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr, 
				gen->arm, gen->mlx_data->window_width - ARM_WIDTH, gen->mlx_data->window_height - ARM_HEIGHT);
	return (0);
}

int	start_window(void)
{
	t_gen	*gen;
	int		w;
	int		h;

	gen = gen_stuff();
	if (mlx_data_init())
		return (1);
	gen->mlx_data->win_ptr = mlx_new_window(gen->mlx_data->mlx_ptr,
			gen->mlx_data->window_width,gen->mlx_data->window_height,"salve");
	if (!gen->mlx_data->win_ptr)
		return (1);
	w = 0;
	h = 0;
	gen->arm = mlx_xpm_file_to_image(	gen->mlx_data->mlx_ptr,
		USER_HAND, &w, &h);
	if (!gen->arm)
		return (printf("Error: failed to load arm image\n"), 1);
	mlx_key_hook(gen->mlx_data->win_ptr, handle_exit, NULL);
	mlx_loop_hook(gen->mlx_data->mlx_ptr, put_arm, NULL);
	mlx_loop(gen->mlx_data->mlx_ptr);
	mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->arm);
	return (0);
}
