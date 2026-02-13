/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:23 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/12 23:04:15 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	handle_audio_keys(int key, t_gen *gen)
{
	const char	*audio_files[5] = {"./audio/default1.ogg",
		"./audio/default2.ogg", "./audio/default3.ogg",
		"./audio/default4.ogg", "./audio/default5.ogg"};
	int			index;

	if ((key >= XK_1 && key <= XK_5) && !gen->flags->terror_mode)
	{
		index = key - XK_1;
		gen->flags->music_on = !gen->flags->music_on;
		stop_all_sounds(gen);
		play_sound(gen, audio_files[index]);
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
}

int	key_press(int key, t_gen *gen)
{
	if (key == XK_Escape)
		handle_exit(key);
	handle_movement_keys(key, gen);
	handle_modifier_keys(key, gen);
	handle_view_keys(key, gen);
	handle_toggle_keys(key, gen);
	handle_audio_keys(key, gen);
	return (0);
}

int	key_release(int key, t_gen *gen)
{
	release_movement_keys(key, gen);
	release_modifier_keys(key, gen);
	release_toggle_keys(key, gen);
	return (0);
}
