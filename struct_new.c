/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:34:24 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/12 10:54:12 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"
#include "headers/general.h"

int	init_xpm_paths(t_gen *gen)
{
	gen->xpm_paths = malloc(sizeof(t_xpm_paths));
	if (!gen->xpm_paths)
		return (0);
	if (!png_name_to_xpm(gen, gen->xpm_paths->normal))
		return (0);
	gen->xpm_paths->terror[0] = ft_strdup("imgs/scary4.xpm");
	gen->xpm_paths->terror[1] = ft_strdup("imgs/scary1.xpm");
	gen->xpm_paths->terror[2] = ft_strdup("imgs/scary2.xpm");
	gen->xpm_paths->terror[3] = ft_strdup("imgs/scary3.xpm");
	gen->xpm_paths->ghost[0] = ft_strdup("imgs/ghost_1.xpm");
	gen->xpm_paths->ghost[1] = ft_strdup("imgs/ghost_2.xpm");
	gen->xpm_paths->ghost[2] = ft_strdup("imgs/ghost_3.xpm");
	gen->xpm_paths->ghost[3] = ft_strdup("imgs/ghost_4.xpm");
	gen->xpm_paths->cthulhu[0] = ft_strdup("imgs/cthulhu_1.xpm");
	gen->xpm_paths->cthulhu[1] = ft_strdup("imgs/cthulhu_2.xpm");
	gen->xpm_paths->skeleton[0] = ft_strdup("imgs/skel_1.xpm");
	gen->xpm_paths->skeleton[1] = ft_strdup("imgs/skel_2.xpm");
	gen->xpm_paths->skeleton[2] = ft_strdup("imgs/skel_3.xpm");
	gen->xpm_paths->skeleton[3] = ft_strdup("imgs/skel_4.xpm");
	gen->xpm_paths->skeleton[4] = ft_strdup("imgs/skel_5.xpm");
	gen->xpm_paths->skeleton[5] = ft_strdup("imgs/skel_6.xpm");
	gen->xpm_paths->skeleton[6] = ft_strdup("imgs/skel_7.xpm");
	gen->xpm_paths->skeleton[7] = ft_strdup("imgs/skel_8.xpm");
	return (1);
}

void	free_xpm_paths(t_xpm_paths *paths)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (i < 2)
			free(paths->cthulhu[i]);
		if (i < 4)
		{
			free(paths->normal[i]);
			free(paths->terror[i]);
			free(paths->ghost[i]);
		}
		free(paths->skeleton[i]);
		i++;
	}
}

static void	load_all_textures(t_gen *gen, t_xpm_paths *paths)
{
	load_textures(gen, gen->texture, paths->normal, 4);
	load_textures(gen, gen->terror_texture, paths->terror, 4);
	load_textures(gen, gen->ghost_enemy, paths->ghost, 4);
	load_textures(gen, gen->cthulhu_enemy, paths->cthulhu, 2);
	load_textures(gen, gen->skeleton_enemy, paths->skeleton, 8);
	gen->door_texture = load_xpm_texture(gen->mlx_data->mlx_ptr,
			"imgs/porta_normal.xpm");
	gen->door_texture2 = load_xpm_texture(gen->mlx_data->mlx_ptr,
			"imgs/terror_door.xpm");
}

void	wall_textures_init(t_gen *gen)
{
	if (!init_xpm_paths(gen))
	{
		ft_putstr_fd("Failed to convert normal PNG names\n", 2);
		exit(1);
	}
	load_all_textures(gen, gen->xpm_paths);
	free_xpm_paths(gen->xpm_paths);
	free(gen->xpm_paths);
	gen->xpm_paths = NULL;
}

int	init_all(t_gen *gen)
{
	gen->mlx_data = malloc(sizeof(t_mlx_data));
	if (!gen->mlx_data)
		return (1);
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
	arm_init(gen);
	terror_arm_init(gen);
	general_texture_init(gen);
	wall_textures_init(gen);
	mouse_init(gen);
	init_flags(gen);
	def_values_init(gen);
	enemy_init(gen);
	enemy_texture_init(gen);
	return (0);
}
