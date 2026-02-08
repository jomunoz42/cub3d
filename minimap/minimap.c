#include "../headers/cub3d.h"

void	draw_minimap_player(t_gen *gen)
{
	int	center_tile;
	int	px;
	int	py;

	center_tile = gen->minimap->zoom_level / 2;
	px = center_tile * MINIMAP_TILE_PIXELS;
	py = center_tile * MINIMAP_TILE_PIXELS;
	for (int y = 0; y < MINIMAP_TILE_PIXELS; y++)
	{
		for (int x = 0; x < MINIMAP_TILE_PIXELS; x++)
		{
			copied_mlx_pixel_put(gen->img_data, px + x, py + y,
				MINIMAP_PLAYER_CLR);
		}
	}
}

void	draw_minimap_fov(t_gen *gen)
{
	int i, num_rays = 20;
	double camera_x, ray_direction_x, ray_direction_y;
	for (i = 0; i < num_rays; i++)
	{
		camera_x = 2.0 * i / (num_rays - 1) - 1.0;
		ray_direction_x = gen->player->dir_x + gen->player->plane_x * camera_x;
		ray_direction_y = gen->player->dir_y + gen->player->plane_y * camera_x;
		direction_hits_wall(gen, ray_direction_x, ray_direction_y);
	}
}

int	is_wall(t_gen *gen, int map_x, int map_y)
{
	int	row_len;

	if (map_y < 0 || map_y >= gen->parse->height)
		return (1);
	row_len = ft_strlen(gen->parse->map[map_y]);
	if (map_x < 0 || map_x >= row_len)
		return (1);
	return (gen->parse->map[map_y][map_x] == '1');
}

void	draw_minimap(t_gen *gen)
{
	int	start_x;
	int	start_y;
	int	map_x;
	int	map_y;
	int	row_len;
			int color;

	start_x = (int)gen->player->x - gen->minimap->zoom_level / 2;
	start_y = (int)gen->player->y - gen->minimap->zoom_level / 2;
	for (int y = 0; y < gen->minimap->zoom_level; y++)
	{
		for (int x = 0; x < gen->minimap->zoom_level; x++)
		{
			map_x = start_x + x;
			map_y = start_y + y;
			if (map_x < 0 || map_y < 0 || map_y >= gen->parse->height)
				continue ;
			row_len = ft_strlen(gen->parse->map[map_y]);
			if (map_x >= row_len)
				continue ;
			if (gen->parse->map[map_y][map_x] == '1')
				color = MINIMAP_WALL_CLR;
			else
				color = MINIMAP_GROUND_CLR;
			for (int py = 0; py < MINIMAP_TILE_PIXELS; py++)
				for (int px = 0; px < MINIMAP_TILE_PIXELS; px++)
					copied_mlx_pixel_put(gen->img_data, x * MINIMAP_TILE_PIXELS
						+ px, y * MINIMAP_TILE_PIXELS + py, color);
		}
	}
	if (gen->flags->enemy_mini)
		draw_enemy_minimap(gen);
	draw_minimap_player(gen);
	draw_minimap_fov(gen);
}
