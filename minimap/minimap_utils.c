#include "../headers/cub3d.h"

void ciclope_dos_xman(t_img_data *img,int x0, int y0, int x1, int y1, int color)
{
	int distance_x_total;
	int distance_y_total;
	int direction_of_x;
	int direction_of_y; //quando eu andar em ym vou pra direita ou pra esqueda?
	int err;
	int err_times_2;

	distance_x_total = abs(x1 - x0); //quantos puxels andar no x
	distance_y_total = abs(y1 - y0); // quantos pixel andar no y
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

void draw_minimap_fov(t_gen *gen) 
{
	int		i;
	int		num_rays;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;

	num_rays = 20; // quantos raios no cone

	i = 0;
	while (i < num_rays)
	{
		cameraX = 2.0 * i / (num_rays - 1) - 1.0;

		rayDirX = gen->player->dir_x
			+ gen->player->plane_x * cameraX;
		rayDirY = gen->player->dir_y
			+ gen->player->plane_y * cameraX;

		direction_hits_wall(gen, rayDirX, rayDirY);
		i++;
	}
}

//manda uma linha vermelha
//inicio em (0:0)
//final em (6, 3)
// y
// 3 |            *
// 2 |        *
// 1 |    *
// 0 |*
//   +---------------- x
//     0 1 2 3 4 5 6
// distance_x_total = |6 - 0| = 6   // anda 6 pixels no eixo X
// distance_y_total = |3 - 0| = 3   // anda 3 pixels no eixo Y

// direction_of_x = +1   // anda para a direita
// direction_of_y = +1   // anda para cima

// err = distance_x_total - distance_y_total ==> 6 - 3 ==> 3

// y = m*x
//m = dy/dy

//ve se a direcao que tamo olhando bateu numa parece
void direction_hits_wall(t_gen *gen, double rayDirX, double rayDirY)
{
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	int		mapX; //atual_tile_x
	int		mapY; // atual_tile_y
	int		stepX;
	int		stepY;
	int		hit;

	mapX = (int)gen->player->x;
	mapY = (int)gen->player->y;

	deltaDistX = fabs(5 / rayDirX); //basicamente a distancia entre linhas vertis
	deltaDistY = fabs(5 / rayDirY);	//basicamente a distancia entre linhas horizontais

// ########
// 	|   |   |   |
//  |   | P |   | cruzar um linha vertical muda x, uma horizontal muda y
//  |   |   |   |
// ########
	if (rayDirX < 0)
	{
		stepX = -1; //raio pra esquerda
		sideDistX = (gen->player->x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1; //raio pra direita
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
	while (!hit) //base da 
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

	ciclope_dos_xman(&gen->minimap->image, px0, py0, px1, py1, 0xFF0000);
}