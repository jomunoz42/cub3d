#include "./headers/cub3d.h"

void search_in_matrix(t_gen *gen, int character)
{
    int row = 0;
    while (gen->parse->map[row])
    {
        int col = 0;
        while (gen->parse->map[row][col])
        {
            if (gen->parse->map[row][col] == character)
            {
                gen->player->x = col + 0.5;
                gen->player->y = row + 0.5;

                gen->player->dir_x = 0;
                gen->player->dir_y = -1;
                gen->player->plane_x = 0.66;
                gen->player->plane_y = 0;
                return;
            }
            col++;
        }
        row++;
    }
}

int get_player_position(t_gen *gen)
{
    search_in_matrix(gen, 'N');
    return (0);
}

void	ciclope_dos_xman(t_gen *gen)
{
	double	ray_x;
	double	ray_y;
	double	step;
	int		map_x;
	int		map_y;
	int		px;
	int		py;

	if (!gen || !gen->player || !gen->parse || !gen->parse->map)
		return;

	ray_x = gen->player->x;
	ray_y = gen->player->y;
	step = 0.08;

	while (1)
	{
		map_x = (int)ray_x;
		map_y = (int)ray_y;

		if (map_y < 0 || map_x < 0
			|| !gen->parse->map[map_y]
			|| !gen->parse->map[map_y][map_x])
			break;
		if (gen->parse->map[map_y][map_x] == '1')
			break;
		px = (int)(ray_x * MINIMAP_SCALE);
		py = (int)(ray_y * MINIMAP_SCALE);
		if (px >= 0 && px < gen->minimap->width
			&& py >= 0 && py < gen->minimap->height)
			copied_mlx_pixel_put(&gen->minimap->image, px, py, 0xFF0000);
		ray_x += gen->player->dir_x * step;
		ray_y += gen->player->dir_y * step;
	}
}

void draw_line(t_img_data *img,
	int x0, int y0, int x1, int y1, int color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx - dy;

	while (1)
	{
		copied_mlx_pixel_put(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}


void draw_minimap_ray_dda_dir(t_gen *gen, double rayDirX, double rayDirY)
{
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		mapX;
	int		mapY;
	int		stepX;
	int		stepY;
	int		hit;

	mapX = (int)gen->player->x;
	mapY = (int)gen->player->y;

	deltaDistX = fabs(1 / rayDirX);
	deltaDistY = fabs(1 / rayDirY);

	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (gen->player->x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - gen->player->x) * deltaDistX;
	}

	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (gen->player->y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - gen->player->y) * deltaDistY;
	}

	hit = 0;
	while (!hit)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
		}
		if (gen->parse->map[mapY][mapX] == '1')
			hit = 1;
	}

	int px0 = gen->player->x * MINIMAP_SCALE;
	int py0 = gen->player->y * MINIMAP_SCALE;
	int px1 = (mapX + 0.5) * MINIMAP_SCALE;
	int py1 = (mapY + 0.5) * MINIMAP_SCALE;

	draw_line(&gen->minimap->image, px0, py0, px1, py1, 0xFF0000);
}


void draw_minimap_fov(t_gen *gen)
{
	int		i;
	int		num_rays;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;

	num_rays = 100; // quantos raios no cone

	i = 0;
	while (i < num_rays)
	{
		cameraX = 2.0 * i / (num_rays - 1) - 1.0;

		rayDirX = gen->player->dir_x
			+ gen->player->plane_x * cameraX;
		rayDirY = gen->player->dir_y
			+ gen->player->plane_y * cameraX;

		draw_minimap_ray_dda_dir(gen, rayDirX, rayDirY);
		i++;
	}
}
