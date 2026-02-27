/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:51:04 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/27 19:06:04 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_arm_object(t_gen *gen, t_img_data *arm)
{
	if (!arm)
		return ;
	if (arm && arm->img && gen->mlx_data && gen->mlx_data->mlx_ptr)
		mlx_destroy_image(gen->mlx_data->mlx_ptr, arm->img);
}

void	free_game_assets(t_gen *gen, int sound)
{
	if (sound == 1)
	{
		free_arm_object(gen, gen->arm);
		stop_all_sounds(gen);
	}
	if (gen->xpm_paths)
	{
		free_xpm_paths(gen->xpm_paths);
		free(gen->xpm_paths);
	}
	if (gen->arm)
		free(gen->arm);
	free_game_objects(gen);
	free_all_resources(gen);
	if (gen->terror_arm)
	{
		if (gen->terror_arm->img)
			mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->terror_arm->img);
		free(gen->terror_arm);
	}
}

void	free_systems_and_mlx(t_gen *gen)
{
	free_input_and_raycast(gen);
	free_config_and_parsing(gen);
	free_exit(gen);
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
}
