#include "./headers/cub3d.h"
#include "headers/general.h"
#include "headers/mlx.h"

int draw_arm(void *param)
{
	t_gen *gen;

	if (!param)
		return (0);
	gen = (t_gen *)param;
	if (!gen->arm)
		return (0);

	mlx_put_image_to_window(
		gen->mlx_data->mlx_ptr,
		gen->mlx_data->win_ptr,
		gen->arm,
		gen->mlx_data->window_width - gen->texture_data->arm_width,
		gen->mlx_data->window_height - gen->texture_data->arm_height
	);
	return (0);
}



void draw_minimap(t_gen *gen)
{
	if (!gen || !gen->parse || !gen->parse->map)
		return;

	for (int row = 0; gen->parse->map[row]; row++)
	{
		for (int col = 0; gen->parse->map[row][col]; col++)
		{
			int color;

			if (gen->parse->map[row][col] == '1')
				color = 0xFFFFFF;
			else if (gen->parse->map[row][col] == '0')
				color = 0x161616;
			else if (gen->parse->map[row][col] == 'N')
				color = 0xFFA500;
			else
				continue;

			for (int dy = 0; dy < MINIMAP_SCALE; dy++)
			{
				for (int dx = 0; dx < MINIMAP_SCALE; dx++)
				{
					copied_mlx_pixel_put(
						&gen->minimap->image,
						col * MINIMAP_SCALE + dx,
						row * MINIMAP_SCALE + dy,
						color
					);
				}
			}
		}
	}

	mlx_put_image_to_window(
		gen->mlx_data->mlx_ptr,
		gen->mlx_data->win_ptr,
		gen->minimap->image.img,
		0, 0
	);
}



void	genesis(t_gen *gen)
{
	int	color;

	int x, y;
	gen->img_data->img = mlx_new_image(gen->mlx_data->mlx_ptr,
			gen->mlx_data->window_width, gen->mlx_data->window_height);
	gen->img_data->addr = mlx_get_data_addr(gen->img_data->img,
			&gen->img_data->bits_per_pixel, &gen->img_data->line_len,
			&gen->img_data->endian);
	for (y = 0; y < gen->mlx_data->window_height; y++)
	{
		for (x = 0; x < gen->mlx_data->window_width; x++)
		{
			color = (y < gen->texture_data->horizon) ? gen->texture_data->clng_color : gen->texture_data->flr_color;
			copied_mlx_pixel_put(gen->img_data, x, y, color);
		}
	}
	mlx_put_image_to_window(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,
		gen->img_data->img, 0, 0);
	mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->img_data->img);
}

int	start_window(t_gen *gen)
{
	int		w;
	int		h;

	w = 0;
	h = 0;
	gen->mlx_data->win_ptr = mlx_new_window(gen->mlx_data->mlx_ptr,
			gen->mlx_data->window_width, gen->mlx_data->window_height, "salve");
	if (!gen->mlx_data->win_ptr)
		return (1);
	gen->arm = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr, USER_HAND_XPM, &w,
			&h);
	if (!gen->arm)
		return (printf("Error: failed to load arm image\n"), 1);
	mlx_key_hook(gen->mlx_data->win_ptr, handle_exit, NULL);
	genesis(gen);
	mlx_loop_hook(gen->mlx_data->mlx_ptr, draw_arm, gen);
	gen->minimap->image.img = mlx_new_image(gen->mlx_data->mlx_ptr, gen->minimap->width, gen->minimap->height);
	gen->minimap->image.addr = mlx_get_data_addr(gen->minimap->image.img , &gen->minimap->image.bits_per_pixel, &gen->minimap->image.line_len, &gen->minimap->image.endian);
	draw_minimap(gen);

	mlx_loop(gen->mlx_data->mlx_ptr);
	mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->arm);
	return (0);
}
