#include "../headers/cub3d.h"

bool	is_out_of_bounds(t_gen *gen, int y, int x)
{
	if (y < 0 || y >= gen->parse->height)
		return (true);
	if (x < 0 || x >= (int)strlen(gen->parse->map[y]))
		return (true);
	return (false);
}

bool	is_blocked(t_gen *gen, int y, int x)
{
	if (gen->parse->map[y][x] == '1')
		return (true);
	if (gen->parse->map[y][x] == 'D')
		return (true);
	return (false);
}

bool	collision(t_gen *gen, double next_y, double next_x)
{
	int		map_y;
	int		map_x;
	int		top;
	int		bottom;
	int		left;
	int		right;
	double	radius;

	map_y = (int)next_y;
	map_x = (int)next_x;
	if (is_out_of_bounds(gen, map_y, map_x))
		return (true);
	radius = 0.2;
	top = (int)(next_y - radius);
	bottom = (int)(next_y + radius);
	left = (int)(next_x - radius);
	right = (int)(next_x + radius);
	if (top >= 0 && left >= 0 && !is_out_of_bounds(gen, top, left))
		if (is_blocked(gen, top, left))
			return (true);
	if (top >= 0 && right >= 0 && !is_out_of_bounds(gen, top, right))
		if (is_blocked(gen, top, right))
			return (true);
	if (bottom >= 0 && left >= 0 && !is_out_of_bounds(gen, bottom, left))
		if (is_blocked(gen, bottom, left))
			return (true);
	if (bottom >= 0 && right >= 0 && !is_out_of_bounds(gen, bottom, right))
		if (is_blocked(gen, bottom, right))
			return (true);
	return (false);
}

int	key_press(int key, t_gen *gen)
{
	const char	*audio_files[5] = {"./audio/default1.mp3",
			"./audio/default2.mp3", "./audio/default3.mp3",
			"./audio/default4.mp3", "./audio/default5.mp3"};
	int			index;

	if (key == XK_Escape)
	{
		handle_exit(key);
	}
	if (key == XK_w)
	{
		gen->kboard->key_w = true;
	}
	if (key == XK_s)
	{
		gen->kboard->key_s = true;
	}
	if (key == XK_a)
	{
		gen->kboard->key_a = true;
	}
	if (key == XK_d)
	{
		gen->kboard->key_d = true;
	}
	if (key == XK_Tab)
	{
		gen->kboard->tab = true;
	}
	if (key == XK_Left)
	{
		gen->kboard->key_left = true;
	}
	if (key == XK_Right)
	{
		gen->kboard->key_right = true;
	}
	if (key == XK_Control_L)
	{
		gen->kboard->control_left = true;
		if (gen->flags->terror_mode)
		{
			gen->player->move_speed = gen->def_values->terror_player_move_speed
				/* + 0.03 */;
			gen->enemy->move_speed =
				/* gen->player->move_speed
-  */ 0.00000002;
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
	if (key == XK_t && !gen->kboard->key_t)
	{
		gen->kboard->key_t = true;
		stop_all_sounds(gen);
		gen->player->move_speed = 0.1;
		gen->enemy->move_speed = gen->player->move_speed;
		gen->flags->terror_mode = !gen->flags->terror_mode;
		start_terror_music(gen);
	}
	if (key == XK_Caps_Lock && !gen->kboard->key_caps_lock)
	{
		gen->kboard->key_caps_lock = true;
		gen->flags->mouse_on = !gen->flags->mouse_on;
	}
	if (key == XK_i && !gen->kboard->key_i)
	{
		gen->kboard->key_i = true;
		gen->flags->info = !gen->flags->info;
	}
	if (key == XK_m && !gen->kboard->key_m)
	{
		gen->kboard->key_m = true;
		gen->flags->minimap = !gen->flags->minimap;
	}
	if (key == XK_e && !gen->kboard->key_m)
	{
		gen->kboard->key_e = true;
		gen->flags->enemy_mini = !gen->flags->enemy_mini;
	}
	if ((key >= XK_1 && key <= XK_5) && !gen->flags->terror_mode)
	{
		index = key - XK_1;
		gen->flags->music_on = !gen->flags->music_on;
		stop_all_sounds(gen);
		play_sound(gen, audio_files[index], 1);
		if (key == XK_1)
			gen->kboard->key_num_one = true;
		if (key == XK_2)
			gen->kboard->key_num_two = true;
		if (key == XK_3)
			gen->kboard->key_num_three = true;
		if (key == XK_4)
			gen->kboard->key_num_four = true;
		if (key == XK_5)
			gen->kboard->key_num_five = true;
	}
	if (key == XK_6 && !gen->flags->terror_mode)
		stop_all_sounds(gen);
	return (0);
}

int	key_release(int key, t_gen *gen)
{
	if (key == XK_w)
	{
		gen->kboard->key_w = false;
	}
	if (key == XK_s)
	{
		gen->kboard->key_s = false;
	}
	if (key == XK_a)
	{
		gen->kboard->key_a = false;
	}
	if (key == XK_d)
	{
		gen->kboard->key_d = false;
	}
	if (key == XK_Tab)
	{
		gen->kboard->tab = false;
	}
	if (key == XK_Left)
	{
		gen->kboard->key_left = false;
	}
	if (key == XK_Right)
	{
		gen->kboard->key_right = false;
	}
	if (key == XK_Control_L)
	{
		if (gen->flags->terror_mode)
		{
			gen->player->move_speed = gen->def_values->terror_player_move_speed;
			gen->enemy->move_speed = gen->player->move_speed - 0.001;
		}
		else
		{
			gen->player->move_speed = 0.05;
			gen->player->rotate_speed = 0.045;
			gen->player->fov -= 0.07;
			gen->kboard->control_left = false;
		}
	}
	if (key == XK_Shift_L)
	{
		gen->player->move_speed = 0.05;
		gen->player->rotate_speed = 0.045;
		gen->kboard->shift_left = false;
	}
	if (key == XK_m)
		gen->kboard->key_m = false;
	if (key == XK_x)
		gen->kboard->key_x = false;
	if (key == XK_z)
		gen->kboard->key_z = false;
	if (key == XK_f)
		gen->kboard->key_f = false;
	if (key == XK_l)
		gen->kboard->key_l = false;
	if (key == XK_t)
	{
		if (!gen->flags->terror_mode) // If we just toggled it off
			stop_all_sounds(gen);
		gen->kboard->key_t = false;
	}
	if (key == XK_Caps_Lock)
		gen->kboard->key_caps_lock = false;
	if (key == XK_i)
		gen->kboard->key_i = false;
	if (key == XK_e)
		gen->kboard->key_e = false;
	return (0);
}
