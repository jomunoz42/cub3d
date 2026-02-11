/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils19.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:44:36 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/11 14:47:01 by vvazzs           ###   ########.fr       */
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
