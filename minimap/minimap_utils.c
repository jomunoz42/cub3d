#include "../headers/cub3d.h"

void	ciclope_dos_xman(t_img_data *img, int x0, int y0, int x1, int y1,
		int color)
{
	double	distance_x_total;
	double	distance_y_total;
	double	direction_of_x;
	double	err;
	double	err_times_2;

	double direction_of_y;
		// quando eu andar em ym vou pra direita ou pra esqueda?
	distance_x_total = ft_abs(x1 - x0); // quantos puxels andar no x
	distance_y_total = ft_abs(y1 - y0); // quantos pixel andar no y
	direction_of_x = (x0 < x1) ? 1 : -1;
	direction_of_y = (y0 < y1) ? 1 : -1;
	err = distance_x_total - distance_y_total;
	while (1)
	{
		copied_mlx_pixel_put(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		err_times_2 = 2 * err;
		if (err_times_2 > -distance_y_total)
		{
			err -= distance_y_total;
			x0 += direction_of_x;
		}
		if (err_times_2 < distance_x_total)
		{
			err += distance_x_total;
			y0 += direction_of_y;
		}
	}
}

void	direction_hits_wall(t_gen *gen, double ray_direction_x,
		double ray_direction_y)
{
	double	start_x;
	double	start_y;
	double	map_x;
	double	map_y;
	double	px0;
	double	py0;
	double	px1;
	double	py1;

	start_x = (int)gen->player->x - gen->minimap->zoom_level / 2;
	start_y = (int)gen->player->y - gen->minimap->zoom_level / 2;
	map_x = (int)gen->player->x;
	map_y = (int)gen->player->y;
	double step_x, step_y, hit = 0;
	double side_dist_x, side_dist_y, delta_dist_x, delta_dist_y;
	delta_dist_x = fabs(5 / ray_direction_x);
	delta_dist_y = fabs(5 / ray_direction_y);
	step_x = (ray_direction_x < 0) ? -1 : 1;
	side_dist_x = (ray_direction_x < 0) ? (gen->player->x - map_x)
		* delta_dist_x : (map_x + 1.0 - gen->player->x) * delta_dist_x;
	step_y = (ray_direction_y < 0) ? -1 : 1;
	side_dist_y = (ray_direction_y < 0) ? (gen->player->y - map_y)
		* delta_dist_y : (map_y + 1.0 - gen->player->y) * delta_dist_y;
	while (!hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			map_x += step_x;
		}
		else
		{
			side_dist_y += delta_dist_y;
			map_y += step_y;
		}
		if (is_wall(gen, map_x, map_y))
			hit = 1;
	}
	px0 = MINIMAP_PIXELS / 2;
	py0 = MINIMAP_PIXELS / 2;
	px1 = (map_x - start_x + 0.5) * MINIMAP_TILE_PIXELS;
	py1 = (map_y - start_y + 0.5) * MINIMAP_TILE_PIXELS;
	px1 = ft_clamp(px1, 0, MINIMAP_PIXELS - 1);
	py1 = ft_clamp(py1, 0, MINIMAP_PIXELS - 1);
	ciclope_dos_xman(gen->img_data, px0, py0, px1, py1, RED_CLR);
}
