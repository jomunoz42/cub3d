/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils11.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:43 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/13 11:16:20 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	handle_movement_keys(int key, t_gen *gen)
{
	if (key == XK_w)
		gen->kboard->key_w = true;
	if (key == XK_s)
		gen->kboard->key_s = true;
	if (key == XK_a)
		gen->kboard->key_a = true;
	if (key == XK_d)
		gen->kboard->key_d = true;
	if (key == XK_Left)
		gen->kboard->key_left = true;
	if (key == XK_Right)
		gen->kboard->key_right = true;
}

void	handle_modifier_keys(int key, t_gen *gen)
{
	if (key == XK_Control_L)
	{
		gen->kboard->control_left = true;
		if (gen->flags->terror_mode)
		{
			gen->player->move_speed = gen->def_values->terror_player_move_speed;
			gen->enemy->move_speed = gen->player->move_speed;
		}
		else
		{
			gen->player->move_speed = gen->def_values->player_move_speed + 0.06;
			gen->player->rotate_speed = 0.060;
			gen->player->fov += 0.07;
		}
	}
	if (key == XK_Shift_L)
	{
		gen->kboard->shift_left = true;
		gen->player->move_speed = 0.01;
		gen->player->rotate_speed = 0.030;
	}
}

void	handle_view_keys(int key, t_gen *gen)
{
	if (key == XK_f)
	{
		gen->kboard->key_f = true;
		gen->player->fov -= 0.01;
	}
	if (key == XK_l)
	{
		gen->kboard->key_l = true;
		gen->player->fov += 0.01;
	}
	if (key == XK_z)
	{
		gen->kboard->key_z = true;
		gen->minimap->zoom_level -= 0.5;
	}
	if (key == XK_x)
	{
		gen->kboard->key_x = true;
		gen->minimap->zoom_level += 0.5;
	}
	if (key == XK_r)
	{
		gen->player->fov = gen->def_values->fov;
		gen->minimap->zoom_level = gen->def_values->minimap_zoom_level;
	}
}

void	toggle_flag(bool *key_state, bool *flag)
{
	if (!*key_state)
	{
		*key_state = true;
		*flag = !*flag;
	}
}

void	handle_toggle_keys(int key, t_gen *gen)
{
	if (key == XK_space)
		gen->kboard->space = true;
	if (key == XK_t && !gen->kboard->key_t)
	{
		gen->kboard->key_t = true;
		stop_all_sounds(gen);
		gen->player->move_speed = 0.1;
		gen->enemy->move_speed = gen->player->move_speed;
		gen->flags->terror_mode = !gen->flags->terror_mode;
		start_terror_music(gen);
	}
	if (key == XK_Caps_Lock)
		toggle_flag(&gen->kboard->key_caps_lock, &gen->flags->mouse_on);
	if (key == XK_i)
		toggle_flag(&gen->kboard->key_i, &gen->flags->info);
	if (key == XK_m)
		toggle_flag(&gen->kboard->key_m, &gen->flags->minimap);
	if (key == XK_e)
		toggle_flag(&gen->kboard->key_e, &gen->flags->enemy_mini);
}
