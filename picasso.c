#include "./headers/cub3d.h"

int draw_arm(void *param)
{
	t_gen *gen;

	if (!param)
		return (0);
	gen = (t_gen *)param;
	if (!gen->arm)
		return (0);

	mlx_put_image_to_window(gen->mlx_data->mlx_ptr,gen->mlx_data->win_ptr,gen->arm,
        gen->mlx_data->win_width - gen->texture_data->arm_width,gen->mlx_data->win_height - gen->texture_data->arm_height);
	return (0);
}

void	genesis(t_gen *gen)
{
	int	color;
	int x, y;
	gen->img_data->img = mlx_new_image(gen->mlx_data->mlx_ptr,gen->mlx_data->win_width, gen->mlx_data->win_height);
	gen->img_data->addr = mlx_get_data_addr(gen->img_data->img,&gen->img_data->bits_pixel, &gen->img_data->line_len,&gen->img_data->endian);
	for (y = 0; y < gen->mlx_data->win_height; y++)
	{
		for (x = 0; x < gen->mlx_data->win_width; x++)
		{
			color = (y < gen->texture_data->horizon) ? gen->texture_data->clng_color : gen->texture_data->flr_color;
			copied_mlx_pixel_put(gen->img_data, x, y, color);
		}
	}
	mlx_put_image_to_window(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,
		gen->img_data->img, 0, 0);
	mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->img_data->img);
}