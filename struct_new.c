#include "./headers/cub3d.h"

t_parsing	*parsing_init(void)
{
	t_parsing	*new;

	new = malloc(sizeof(t_parsing));
	if (!new)
		return (NULL);
	*new = (t_parsing){// check and study this later
						.textures_info = NULL,
						.error_messages = {"Error: missing north texture [NO]",
							"Error: missing south texture [SO]",
							"Error: missing west texture [WE]",
							"Error: missing east texture [EA]",
							"Error: missing floor color [F]",
							"Error: missing ceiling color [C]",
							"Error: can't find north texture file",
							"Error: can't find south texture file",
							"Error: can't find west texture file",
							"Error: can't find east texture file",
							"Error: floor color invalid",
							"Error: ceiling color invalid"},
							.fd = 0};
	return (new);
}

int texture_data_init(t_gen *gen)
{
	gen->texture_data = malloc(sizeof(t_texture_data));
	if (!gen->texture_data)
		return (0);
	gen->texture_data->arm_width = 0;
	gen->texture_data->arm_height = 0;
	if (!png_size_fd(USER_HAND_PNG, &gen->texture_data->arm_width, &gen->texture_data->arm_height))
		return (0);
    printf("Width: %u, Height: %u\n", gen->texture_data->arm_width, gen->texture_data->arm_height);
	return (1);

}

int	mlx_data_init(void)
{
	t_gen	*gen;

	gen = gen_stuff();
	texture_data_init(gen);
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
	return (0);
}
