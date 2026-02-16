/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freedom_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:49 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 18:56:36 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	free_minimap(t_gen *gen)
{
	if (!gen->minimap)
		return ;
	if (gen->minimap->image.img && gen->mlx_data && gen->mlx_data->mlx_ptr)
		mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->minimap->image.img);
	if (gen->minimap->map)
		ft_free_matrix(gen->minimap->map);
	free(gen->minimap);
}

void	free_enemies(t_gen *gen)
{
	int	i;

	if (!gen->enemy)
		return ;
	i = 0;
	while (i < 8)
	{
		if (gen->skeleton_enemy[i])
			free(gen->skeleton_enemy[i]);
		i++;
	}
	free(gen->enemy);
}

void	free_game_objects(t_gen *gen)
{
	if (!gen)
		return ;
	free_arm_object(gen, gen->terror_arm);
	free_arm_object(gen, gen->arm);
	free_minimap(gen);
	if (gen->player)
		free(gen->player);
	free_enemies(gen);
}

void	free_input_and_raycast(t_gen *gen)
{
	if (gen->rayhit)
		free(gen->rayhit);
	if (gen->kboard)
		free(gen->kboard);
	if (gen->mouse)
	{
		free(gen->mouse);
	}
	if (gen->door_texture)
		free(gen->door_texture);
	if (gen->door_texture2)
		free(gen->door_texture2);
	if (gen->flags)
		free(gen->flags);
}

void	free_config_and_parsing(t_gen *gen)
{
	if (gen->def_values)
	{
		if (gen->def_values->env)
			ft_free_matrix(gen->def_values->env);
		if (gen->def_values->sounds.pids)
			free(gen->def_values->sounds.pids);
		free(gen->def_values);
	}
	if (gen->parse)
	{
		free_parsing(gen->parse);
		gen->parse = NULL;
	}
	if (gen->texture_data)
		free(gen->texture_data);
	if (gen->img_data)
	{
		free(gen->img_data);
	}
	if (gen->dda)
		free(gen->dda);
}
