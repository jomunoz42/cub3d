/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils30.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:39:38 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/13 22:42:21 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	load_textures(t_gen *gen, t_texture **dst, char **xpm_files, int count)
{
	int	bpp;
	int	sl;
	int	endian;
	int	i;

	i = 0;
	while (i < count)
	{
		dst[i]->img = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr,
				xpm_files[i], &dst[i]->width, &dst[i]->height);
		if (!dst[i]->img)
		{
			printf("Failed to load texture %d: %s\n", i, xpm_files[i]);
			exit(1);
		}
		dst[i]->data = (int *)mlx_get_data_addr(dst[i]->img, &bpp, &sl,
				&endian);
		i++;
	}
}

int exit_init(t_gen *gen)
{
	gen->exit = malloc(sizeof(t_exit));
	if (!gen->exit)
		return (0);
	gen->exit->active = false;
	return (1);
}

void	update_enemy_modes(t_gen *gen)
{
	int	i;

	i = 0;
	while (i < gen->enemy_count)
	{
		if (gen->flags->terror_mode)
		{
			if (gen->enemy[i].type == ENEMY_SKELETON
				|| gen->enemy[i].type == ENEMY_SKELETON2)
				gen->enemy[i].type = HANGED_SKELETON;
		}
		else
			gen->enemy[i].type = gen->enemy[i].first_type;
		i++;
	}
}
