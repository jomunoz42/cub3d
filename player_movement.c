/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 23:45:44 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/11 23:54:45 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"
#include "headers/general.h"
#include "headers/mlx.h"

void	rotate_player(t_gen *gen, double angle)
{
	double	first_direction_x;
	double	first_plane_x;

	first_direction_x = gen->player->dir_x;
	first_plane_x = gen->player->plane_x;
	gen->player->dir_x = gen->player->dir_x * cos(angle) - gen->player->dir_y
		* sin(angle);
	gen->player->dir_y = first_direction_x * sin(angle) + gen->player->dir_y
		* cos(angle);
	gen->player->plane_x = gen->player->plane_x * cos(angle)
		- gen->player->plane_y * sin(angle);
	gen->player->plane_y = first_plane_x * sin(angle) + gen->player->plane_y
		* cos(angle);
}

void	apply_player_movement(t_gen *gen, double nx, double ny)
{
	if (gen->kboard->tab)
	{
		open_close_door(gen);
		gen->kboard->tab = false;
	}
	if (gen->kboard->key_right)
		rotate_player(gen, gen->player->rotate_speed);
	if (gen->kboard->key_left)
		rotate_player(gen, -gen->player->rotate_speed);
	if (!collision(gen, gen->player->y, nx + gen->player_move->move_x))
		gen->player->x += gen->player_move->move_x;
	if (!collision(gen, ny + gen->player_move->move_y, gen->player->x))
		gen->player->y += gen->player_move->move_y;
	if (!gen->flags->terror_mode && !gen->kboard->control_left)
	{
		if (!gen->kboard->shift_left)
			gen->player->move_speed = 0.05;
	}
}

void	update_player(t_gen *gen)
{
	double	nx;
	double	ny;

	nx = gen->player->x;
	ny = gen->player->y;
	calculate_player_movement(gen);
	apply_player_movement(gen, nx, ny);
}

void	render_frame(t_gen *gen)
{
	int	i;

	clear_image(gen->img_data, 0x000000);
	render_scene(gen);
	i = -1;
	while (++i < gen->enemy_count)
	{
		if (gen->flags->terror_mode || gen->enemy[i].type != ENEMY_SKELETON)
			draw_enemy(gen, i);
	}
	if (!gen->flags->terror_mode && gen->flags->minimap)
		draw_minimap(gen);
	if (gen->flags->terror_mode)
		draw_terror_arm(gen);
	else
		draw_arm(gen);
	apply_vignette_to_image(gen, gen->img_data);
	mlx_put_image_to_window(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,
		gen->img_data->img, 0, 0);
	if (gen->flags->info && !gen->flags->terror_mode)
		print_info(gen);
}

int	game_loop(t_gen *gen)
{
	update_game_state(gen);
	render_frame(gen);
	return (0);
}
