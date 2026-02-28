/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:34:24 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/28 09:16:34 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_skeleton_alloc(t_gen *gen, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (!gen->xpm_paths->skeleton[i])
		{
			write (2, "Error\nMalloc failed\n", 21);
			while (--i >= 0)
				free(gen->xpm_paths->skeleton[i]);
			free(gen->xpm_paths);
			super_duper_hiper_free();
		}
		i++;
	}
}

int	init_xpm_paths(t_gen *gen)
{
	gen->xpm_paths = malloc(sizeof(t_xpm_paths));
	if (!gen->xpm_paths)
		return (0);
	if (!png_name_to_xpm(gen, gen->xpm_paths->normal))
		return (0);
	gen->xpm_paths->skeleton[0] = ft_strdup("imgs/skel_1.xpm");
	gen->xpm_paths->skeleton[1] = ft_strdup("imgs/skel_2.xpm");
	gen->xpm_paths->skeleton[2] = ft_strdup("imgs/skel_3.xpm");
	gen->xpm_paths->skeleton[3] = ft_strdup("imgs/skel_4.xpm");
	gen->xpm_paths->skeleton[4] = ft_strdup("imgs/skel_5.xpm");
	gen->xpm_paths->skeleton[5] = ft_strdup("imgs/skel_6.xpm");
	gen->xpm_paths->skeleton[6] = ft_strdup("imgs/skel_7.xpm");
	gen->xpm_paths->skeleton[7] = ft_strdup("imgs/skel_8.xpm");
	check_skeleton_alloc(gen, 8);
	return (1);
}

void	free_xpm_paths(t_xpm_paths *paths)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (i < 4)
			free(paths->normal[i]);
		free(paths->skeleton[i]);
		i++;
	}
}

void	load_all_textures(t_gen *gen, t_xpm_paths *paths)
{
	load_textures(gen, gen->texture, paths->normal, 4);
	load_textures(gen, gen->skeleton_enemy, paths->skeleton, 8);
	gen->door_texture = load_xpm_texture(gen->mlx_data->mlx_ptr,
			"imgs/porta_normal.xpm");
}

int	init_all(t_gen *gen)
{
	gen->mlx_data = malloc(sizeof(t_mlx_data));
	if (!gen->mlx_data)
	{
		write(2, "Error\nMalloc failed\n", 21);
		return (free_parsing(gen->parse), 1);
	}
	basic_mlx_init(gen);
	texture_data_init(gen);
	render_scene_init(gen);
	init_draw_enemy(gen);
	player_move_init(gen);
	dda_init(gen);
	avg_img_init(gen);
	player_init(gen);
	minimap_init(gen);
	keyboard_init(gen);
	rayhit_init(gen);
	general_texture_init(gen);
	wall_textures_init(gen);
	mouse_init(gen);
	init_flags(gen);
	def_values_init(gen);
	enemy_init(gen);
	return (0);
}
