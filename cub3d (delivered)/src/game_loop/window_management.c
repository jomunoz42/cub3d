/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:06 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/27 23:17:15 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	window_init(t_gen *gen)
{
	gen->mlx_data->win_ptr = mlx_new_window(gen->mlx_data->mlx_ptr,
			gen->mlx_data->win_width, gen->mlx_data->win_height, WINDOW_NAME);
	if (!gen->mlx_data->win_ptr)
		return (1);
	return (0);
}

int	start_window(t_gen *gen, char *argv)
{
	(void)argv;
	if (window_init(gen) == 1)
	{
		write(2, "Error\nError: cound't initiate window\n", 38);
		return (1);
	}
	get_player_position(gen);
	gen->img_data->img = mlx_new_image(gen->mlx_data->mlx_ptr,
			gen->mlx_data->win_width, gen->mlx_data->win_height);
	gen->img_data->addr = mlx_get_data_addr(gen->img_data->img,
			&gen->img_data->bits_pixel, &gen->img_data->line_len,
			&gen->img_data->endian);
	gen->img_data->height = gen->mlx_data->win_height;
	gen->img_data->width = gen->mlx_data->win_width;
	mlx_hook(gen->mlx_data->win_ptr, 2, KeyPressMask, key_press, gen);
	mlx_hook(gen->mlx_data->win_ptr, 3, KeyReleaseMask, key_release, gen);
	mlx_hook(gen->mlx_data->win_ptr, DestroyNotify, KeyPressMask,
		super_duper_hiper_free, NULL);
	mlx_loop_hook(gen->mlx_data->mlx_ptr, game_loop, gen);
	mlx_loop(gen->mlx_data->mlx_ptr);
	return (0);
}
