/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new_utils4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:40:59 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/27 23:14:57 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_texture_array(t_texture **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		array[i] = malloc(sizeof(t_texture));
		if (!array[i])
		{
			while (--i >= 0)
				free(array[i]);
			return (0);
		}
		array[i]->data = NULL;
		array[i]->height = 0;
		array[i]->width = 0;
		array[i]->img = NULL;
		i++;
	}
	return (1);
}

int	general_texture_init(t_gen *gen)
{
	if (!init_texture_array(gen->texture, 4))
		return (0);
	if (!init_texture_array(gen->skeleton_enemy, 8))
		return (0);
	return (1);
}

int	player_init(t_gen *gen)
{
	gen->player = malloc(sizeof(t_player));
	if (!gen->player)
		return (0);
	gen->player->x = 1;
	gen->player->y = 1;
	gen->player->dir_x = 0;
	gen->player->dir_y = 0;
	gen->player->plane_x = 0;
	gen->player->plane_y = 0;
	gen->player->move_speed = 0.05;
	gen->player->rotate_speed = DEFAULT_PLAYER_ROTATE_SPEED;
	gen->player->fov = DEFAULT_PLAYER_FOV;
	return (1);
}
