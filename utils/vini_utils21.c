/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils21.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 23:54:34 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/11 23:55:03 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	update_game_state(t_gen *gen)
{
	int		i;
	double	dist;

	update_player(gen);
	i = -1;
	while (++i < gen->enemy_count)
	{
		gen->enemy[i].move_speed = 0.02;
		// if (gen->enemy[i].type != ENEMY_SKELETON)
		// 	update_enemy(gen, i);
		update_enemy_animation(gen->enemy, i);
		dist = sqrt(pow(gen->enemy[i].x - gen->player->x, 2)
				+ pow(gen->enemy[i].y - gen->player->y, 2));
		if (dist <= 0.65 && gen->flags->terror_mode)
		{
			printf("You are dead\n");
			super_duper_hiper_free();
			exit(1);
		}
	}
	mouse_looking(gen);
}
