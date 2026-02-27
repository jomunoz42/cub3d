/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:36:14 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/27 21:06:00 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	enemy_visible(t_gen *gen, double *distance_out, int i)
{
	double	delta[2];
	double	distance;

	delta[0] = gen->enemy[i].x - gen->player->x;
	delta[1] = gen->enemy[i].y - gen->player->y;
	distance = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	if (distance_out)
		*distance_out = distance;
	if (distance > FOG_END)
		return (false);
	return (raycast_clear(gen, delta[0], delta[1], distance));
}
