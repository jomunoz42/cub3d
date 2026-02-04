#include "../headers/cub3d.h"

void ciclope_dos_xman(t_img_data *img,int x0, int y0, int x1, int y1, int color)
{
	int distance_x_total;
	int distance_y_total;
	int direction_of_x;
	int direction_of_y; //quando eu andar em ym vou pra direita ou pra esqueda?
	int err;
	int err_times_2;

	distance_x_total = ft_abs(x1 - x0); //quantos puxels andar no x
	distance_y_total = ft_abs(y1 - y0); // quantos pixel andar no y
	direction_of_x = (x0 < x1) ? 1 : -1;
	direction_of_y = (y0 < y1) ? 1 : -1;
	err = distance_x_total - distance_y_total;
	while (1)
	{
		copied_mlx_pixel_put(img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break;
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

void direction_hits_wall(t_gen *gen, double rayDirX, double rayDirY)
{
    int start_x = (int)gen->player->x - ZOOM_LEVEL / 2;
    int start_y = (int)gen->player->y - ZOOM_LEVEL / 2;

    int mapX = (int)gen->player->x;
    int mapY = (int)gen->player->y;
    int stepX, stepY, hit = 0;
    double sideDistX, sideDistY, deltaDistX, deltaDistY;

    deltaDistX = fabs(5 / rayDirX);
    deltaDistY = fabs(5 / rayDirY);

    stepX = (rayDirX < 0) ? -1 : 1;
    sideDistX = (rayDirX < 0) ? (gen->player->x - mapX) * deltaDistX : (mapX + 1.0 - gen->player->x) * deltaDistX;

    stepY = (rayDirY < 0) ? -1 : 1;
    sideDistY = (rayDirY < 0) ? (gen->player->y - mapY) * deltaDistY : (mapY + 1.0 - gen->player->y) * deltaDistY;

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
        if (is_wall(gen, mapX, mapY))
            hit = 1;
    }

    int px0 = MINIMAP_PIXELS / 2;
    int py0 = MINIMAP_PIXELS / 2;
    int px1 = (mapX - start_x + 0.5) * MINIMAP_TILE_PIXELS;
    int py1 = (mapY - start_y + 0.5) * MINIMAP_TILE_PIXELS;
    px1 = clamp(px1, 0, MINIMAP_PIXELS - 1);
    py1 = clamp(py1, 0, MINIMAP_PIXELS - 1);

    ciclope_dos_xman(gen->img_data, px0, py0, px1, py1, 0xFF0000);
}
