/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:34:24 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/12 10:34:25 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"
#include "headers/general.h"

void	wall_textures_init(t_gen *gen)
{
	char	*normal_xpm[4];
	char	*terror_xpm[4];
	char	*ghost_xpm[4];
	char	*cthulhu_xpm[4];
	char	*skeleton_xpm[8];
	int		i;

	if (!png_name_to_xpm(gen, normal_xpm))
	{
		ft_putstr_fd("Failed to convert normal PNG names\n", 2);
		exit(1);
	}
	terror_xpm[0] = ft_strdup("imgs/scary4.xpm");
	terror_xpm[1] = ft_strdup("imgs/scary1.xpm");
	terror_xpm[2] = ft_strdup("imgs/scary2.xpm");
	terror_xpm[3] = ft_strdup("imgs/scary3.xpm");
	ghost_xpm[0] = ft_strdup("imgs/ghost_1.xpm");
	ghost_xpm[1] = ft_strdup("imgs/ghost_2.xpm");
	ghost_xpm[2] = ft_strdup("imgs/ghost_3.xpm");
	ghost_xpm[3] = ft_strdup("imgs/ghost_4.xpm");
	cthulhu_xpm[0] = ft_strdup("imgs/cthulhu_1.xpm");
	cthulhu_xpm[1] = ft_strdup("imgs/cthulhu_2.xpm");
	skeleton_xpm[0] = ft_strdup("imgs/skel_1.xpm");
	skeleton_xpm[1] = ft_strdup("imgs/skel_2.xpm");
	skeleton_xpm[2] = ft_strdup("imgs/skel_3.xpm");
	skeleton_xpm[3] = ft_strdup("imgs/skel_4.xpm");
	skeleton_xpm[4] = ft_strdup("imgs/skel_5.xpm");
	skeleton_xpm[5] = ft_strdup("imgs/skel_6.xpm");
	skeleton_xpm[6] = ft_strdup("imgs/skel_7.xpm");
	skeleton_xpm[7] = ft_strdup("imgs/skel_8.xpm");
	load_textures(gen, gen->texture, normal_xpm, 4);
	load_textures(gen, gen->terror_texture, terror_xpm, 4);
	load_textures(gen, gen->ghost_enemy, ghost_xpm, 4);
	load_textures(gen, gen->cthulhu_enemy, cthulhu_xpm, 2);
	load_textures(gen, gen->skeleton_enemy, skeleton_xpm, 8);
	gen->door_texture = load_xpm_texture(gen->mlx_data->mlx_ptr,
			"imgs/porta_normal.xpm");
	gen->door_texture2 = load_xpm_texture(gen->mlx_data->mlx_ptr,
			"imgs/terror_door.xpm");
	i = 0;
	while (i < 8)
	{
		if (i < 2)
			free(cthulhu_xpm[i]);
		if (i < 4)
		{
			free(normal_xpm[i]);
			free(terror_xpm[i]);
			free(ghost_xpm[i]);
		}
		free(skeleton_xpm[i]);
		i++;
	}
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
