/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:50:44 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/11 14:58:09 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	init_line(int *coords, int *vars)
{
	vars[0] = ft_abs(coords[2] - coords[0]);
	vars[1] = ft_abs(coords[3] - coords[1]);

	if (coords[0] < coords[2])
		vars[2] = 1;
	else
		vars[2] = -1;

	if (coords[1] < coords[3])
		vars[3] = 1;
	else
		vars[3] = -1;

	vars[4] = vars[0] - vars[1];
}


void	draw_line(t_img_data *img, int *coords, int *vars, int color)
{
	int	err2;

	while (1)
	{
		copied_mlx_pixel_put(img, coords[0], coords[1], color);
		if (coords[0] == coords[2] && coords[1] == coords[3])
			break ;
		err2 = 2 * vars[4];
		if (err2 > -vars[1])
		{
			vars[4] = vars[4] - vars[1];
			coords[0] = coords[0] + vars[2];
		}
		if (err2 < vars[0])
		{
			vars[4] = vars[4] + vars[0];
			coords[1] = coords[1] + vars[3];
		}
	}
}

void	ciclope_dos_xman(t_img_data *img, int *coords, int color)
{
	int	vars[5];

	init_line(coords, vars);
	draw_line(img, coords, vars, color);
}



void	init_dda(t_gen *gen, double ray_dir_x, double ray_dir_y, double *vars)
{
	double	map_x;
	double	map_y;
	double	player_x;
	double	player_y;

	player_x = gen->player->x;
	player_y = gen->player->y;
	map_x = (int)player_x;
	map_y = (int)player_y;
	vars[0] = map_x;
	vars[1] = map_y;
	vars[2] = fabs(5 / ray_dir_x);
	vars[3] = fabs(5 / ray_dir_y);
	if (ray_dir_x < 0)
		vars[4] = -1;
	else
		vars[4] = 1;
	if (ray_dir_x < 0)
		vars[5] = (player_x - map_x) * vars[2];
	else
		vars[5] = (map_x + 1.0 - player_x) * vars[2];
	if (ray_dir_y < 0)
		vars[6] = -1;
	else
		vars[6] = 1;
	if (ray_dir_y < 0)
		vars[7] = (player_y - map_y) * vars[3];
	else
		vars[7] = (map_y + 1.0 - player_y) * vars[3];
}


void	perform_dda(t_gen *gen, double *vars)
{
	double	hit;

	hit = 0;
	while (!hit)
	{
		if (vars[5] < vars[7])
		{
			vars[5] = vars[5] + vars[2];
			vars[0] = vars[0] + vars[4];
		}
		else
		{
			vars[7] = vars[7] + vars[3];
			vars[1] = vars[1] + vars[6];
		}
		if (is_wall(gen, vars[0], vars[1]))
			hit = 1;
	}
}

void	draw_ray_minimap(t_gen *gen, double *vars)
{
	double	start_x;
	double	start_y;
	double	px1;
	double	py1;
	int		coords[4];

	start_x = (int)gen->player->x - gen->minimap->zoom_level / 2;
	start_y = (int)gen->player->y - gen->minimap->zoom_level / 2;

	px1 = (vars[0] - start_x + 0.5) * MINIMAP_TILE_PIXELS;
	py1 = (vars[1] - start_y + 0.5) * MINIMAP_TILE_PIXELS;

	px1 = ft_clamp(px1, 0, MINIMAP_PIXELS - 1);
	py1 = ft_clamp(py1, 0, MINIMAP_PIXELS - 1);

	coords[0] = MINIMAP_PIXELS / 2;
	coords[1] = MINIMAP_PIXELS / 2;
	coords[2] = (int)px1;
	coords[3] = (int)py1;

	ciclope_dos_xman(gen->img_data, coords, RED_CLR);
}


void	direction_hits_wall(t_gen *gen, double ray_dir_x, double ray_dir_y)
{
	double	vars[8];

	init_dda(gen, ray_dir_x, ray_dir_y, vars);
	perform_dda(gen, vars);
	draw_ray_minimap(gen, vars);
}
