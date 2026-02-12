/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:05:41 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/12 10:51:14 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"
#include "headers/mlx.h"

int	handle_exit(int keysys)
{
	if (keysys == XK_Escape)
		return (super_duper_hiper_free(), 1);
	return (0);
}

void	free_images(t_gen *gen)
{
	if (!gen || !gen->img_data)
		return ;
	if (gen->img_data->vignette)
		free(gen->img_data->vignette);
	if (gen->img_data->img && gen->mlx_data && gen->mlx_data->mlx_ptr)
		mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->img_data->img);
	free(gen->img_data);
	gen->img_data = NULL;
}

void	free_textures(t_gen *gen)
{
	int	i;

	if (!gen)
		return ;
	i = -1;
	while (++i < 4)
	{
		if (gen->texture[i])
		{
			if (gen->mlx_data && gen->mlx_data->mlx_ptr)
				mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->texture[i]->img);
			free(gen->texture[i]);
			gen->texture[i] = NULL;
		}
		if (gen->terror_texture[i])
		{
			free(gen->terror_texture[i]);
			gen->terror_texture[i] = NULL;
		}
	}
	if (gen->enemy_tex && gen->mlx_data)
	{
		free_texture(gen->mlx_data->mlx_ptr, gen->enemy_tex);
		gen->enemy_tex = NULL;
	}
}

void	free_all_resources(t_gen *gen)
{
	free_images(gen);
	free_textures(gen);
	if (gen->render)
		free(gen->render);
	if (gen->player_move)
		free(gen->player_move);
	if (gen->draw_enemy)
		free(gen->draw_enemy);
}

int	super_duper_hiper_free(void)
{
	t_gen	*gen;

	gen = gen_stuff();
	stop_all_sounds(gen);
	free_all_resources(gen);
	free_game_objects(gen);
	free_input_and_raycast(gen);
	free_config_and_parsing(gen);
	if (gen->mlx_data)
	{
		if (gen->mlx_data->win_ptr)
			mlx_destroy_window(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr);
		if (gen->mlx_data->mlx_ptr)
		{
			mlx_destroy_display(gen->mlx_data->mlx_ptr);
			free(gen->mlx_data->mlx_ptr);
		}
		free(gen->mlx_data);
	}
	exit(0);
}
