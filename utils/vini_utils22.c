/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils22.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:43:03 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/12 16:49:17 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

bool	raycast_clear(t_gen *gen, double dx, double dy, double distance)
{
	double	x;
	double	y;
	double	step[2];
	double	traveled;

	step[0] = dx / distance * 0.1;
	step[1] = dy / distance * 0.1;
	x = gen->player->x;
	y = gen->player->y;
	traveled = 0;
	while (traveled < distance)
	{
		if (gen->parse->map[(int)y][(int)x] == '1')
			return (false);
		x += step[0];
		y += step[1];
		traveled += 0.1;
	}
	return (true);
}

bool	enemy_visible(t_gen *gen, double *distance_out, int i)
{
	double	delta[2];
	double	distance;

	delta[0] = gen->enemy[i].x - gen->player->x;
	delta[1] = gen->enemy[i].y - gen->player->y;
	distance = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);
	if (distance_out)
		*distance_out = distance;
	if (distance > FOG_END)
		return (false);
	return (raycast_clear(gen, delta[0], delta[1], distance));
}

void	get_enemy_anim_stats(int type, int *max_frames, int *speed)
{
	if (type == ENEMY_GHOST)
	{
		*max_frames = 4;
		*speed = 10;
	}
	else if (type == ENEMY_CTHULHU)
	{
		*max_frames = 2;
		*speed = 25;
	}
	else if (type == ENEMY_SKELETON)
	{
		*max_frames = 7;
		*speed = 8;
	}
	else
	{
		*max_frames = 0;
		*speed = 0;
	}
}

void	update_enemy_animation(t_enemy *enemy, int i)
{
	int	max_frames;
	int	speed;

	get_enemy_anim_stats(enemy[i].type, &max_frames, &speed);
	if (speed <= 0)
		return ;
	enemy[i].enemy_timer++;
	if (enemy[i].enemy_timer >= speed)
	{
		enemy[i].enemy_timer = 0;
		enemy[i].enemy_frame = (enemy[i].enemy_frame + 1) % max_frames;
	}
}

int	enemy_dealer(t_gen *gen, t_texture **tex, t_enemy **enemy, int i)
{
	if (!gen->enemy)
		return (0);
	if (gen->enemy[i].type == ENEMY_GHOST && !gen->ghost_enemy[0])
		return (0);
	if (gen->enemy[i].type == ENEMY_CTHULHU && !gen->cthulhu_enemy[0]
		&& gen->flags->terror_mode)
		return (0);
	if (gen->enemy[i].type == ENEMY_SKELETON && !gen->skeleton_enemy[0])
		return (0);
	*enemy = &gen->enemy[i];
	if ((*enemy)->type == ENEMY_GHOST && gen->flags->terror_mode)
		*tex = gen->ghost_enemy[(*enemy)->enemy_frame];
	else if ((*enemy)->type == ENEMY_CTHULHU && gen->flags->terror_mode)
		*tex = gen->cthulhu_enemy[(*enemy)->enemy_frame];
	else if ((*enemy)->type == ENEMY_SKELETON && !gen->flags->terror_mode)
		*tex = gen->skeleton_enemy[(*enemy)->enemy_frame];
	else
		return (0);
	return (1);
}
