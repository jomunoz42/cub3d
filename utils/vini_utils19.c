/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils19.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:44:36 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/11 15:00:17 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	init_start(t_gen *gen)
{
	gen->dda->start_x = (int)gen->player->x;
	gen->dda->start_y = (int)gen->player->y;
	gen->dda->wall_hit = 0;
	gen->dda->side = 0;
}

void	init_delta(t_gen *gen, double ray_x, double ray_y)
{
	gen->dda->delta_x = fabs(1.0 / ray_x);
	gen->dda->delta_y = fabs(1.0 / ray_y);
}

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
