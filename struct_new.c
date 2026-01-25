#include "./headers/cub3d.h"

t_parsing	*parsing_init(void)
{
	t_parsing	*new;

	new = malloc(sizeof(t_parsing));
	if (!new)
		return (NULL);
	*new = (t_parsing){// check and study this later
						.map = NULL,
						.player = '\0',
						.width = 0,
						.height = 0,
						.fd = 0,
						.elements = {0, 0, 0, 0, 0, 0}
	};
	return (new);
}

int	avg_img_init(t_gen *gen)
{
	gen->img_data = malloc(sizeof(t_img_data));
	if (!gen->img_data)
		return (0);
	gen->img_data->addr = NULL;
	gen->img_data->img = NULL;
	gen->img_data->endian = 0;
	gen->img_data->line_len = 0;
	gen->img_data->bits_per_pixel = 0;
	return (1);
}

int	texture_data_init(t_gen *gen)
{
	gen->texture_data = malloc(sizeof(t_texture_data));
	if (!gen->texture_data)
		return (0);
	gen->texture_data->arm_width = 0;
	gen->texture_data->arm_height = 0;
	// gen->texture_data->clng_color = color_switch(gen->parse->textures_info[4]);
	// gen->texture_data->flr_color = color_switch(gen->parse->textures_info[5]);
	gen->texture_data->horizon = gen->mlx_data->window_height / 2;
	if (!png_size_fd(USER_HAND_PNG, &gen->texture_data->arm_width,
			&gen->texture_data->arm_height))
		return (0);
	printf("[arm image data] Width: %u, Height: %u\n",
		gen->texture_data->arm_width, gen->texture_data->arm_height);
	return (1);
}

int	mlx_data_init(void)
{
	t_gen	*gen;

	gen = gen_stuff();
	gen->mlx_data = malloc(sizeof(t_mlx_data));
	if (!gen->mlx_data)
		return (1);
	gen->mlx_data->mlx_ptr = mlx_init();
	if (!gen->mlx_data->mlx_ptr)
		return (1);
	gen->mlx_data->win_ptr = NULL;
	gen->arm = NULL;
	gen->mlx_data->window_width = WIN_WIDTH;
	gen->mlx_data->window_height = WIN_HEIGHT;
	texture_data_init(gen);
	avg_img_init(gen);
	printf("== horizontal line is on %d\n", gen->texture_data->horizon);
	return (0);
}
