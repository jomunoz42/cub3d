/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:56 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/11 11:02:57 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"
#include "headers/mlx.h"

int	mouse_looking(t_gen *gen)
{
	static int	first_frame = 1;
	int			direction_x;
	int			cursor_y;
	const int	cursor_x = WIN_WIDTH / 2;

	cursor_y = WIN_HEIGHT / 2;
	if (gen->flags->mouse_on)
	{
		mlx_mouse_hide(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr);
		mlx_mouse_get_pos(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,
			&gen->mouse->x, &gen->mouse->y);
		if (!first_frame)
		{
			direction_x = gen->mouse->x - cursor_x;
			if (direction_x != 0)
				rotate_player(gen, direction_x * gen->mouse->sens);
		}
		else
			first_frame = 0;
		mlx_mouse_move(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr, cursor_x,
			cursor_y);
	}
	else
		mlx_mouse_show(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr);
	return (1);
}
