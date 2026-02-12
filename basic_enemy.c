/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:56:34 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/12 09:28:51 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cub3d.h"

static bool	raycast_clear(t_gen *gen, double dx, double dy, double distance)
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

void	update_enemy_animation(t_enemy *enemy, int i)
{
	int	max_frames;
	int	speed;

	if (enemy[i].type == ENEMY_GHOST)
	{
		max_frames = 4;
		speed = 10;
	}
	else if (enemy[i].type == ENEMY_CTHULHU)
	{
		max_frames = 2;
		speed = 25;
	}
	else if (enemy[i].type == ENEMY_SKELETON)
	{
		max_frames = 7;
		speed = 8;
	}
	else
		return ;
	enemy[i].enemy_timer++;
	if (enemy[i].enemy_timer >= speed)
	{
		enemy[i].enemy_timer = 0;
		enemy[i].enemy_frame = (enemy[i].enemy_frame + 1) % max_frames;
	}
}

int enemy_dealer(t_gen *gen, t_texture **tex, t_enemy **enemy, int i)

{
	if (!gen->enemy)
		return(0) ;
	if (gen->enemy[i].type == ENEMY_GHOST && !gen->ghost_enemy[0])
		return(0) ;
	if (gen->enemy[i].type == ENEMY_CTHULHU && !gen->cthulhu_enemy[0]
		&& gen->flags->terror_mode)
		return(0) ;
	if (gen->enemy[i].type == ENEMY_SKELETON && !gen->skeleton_enemy[0])
		return(0) ;
	*enemy = &gen->enemy[i];
	if ((*enemy)->type == ENEMY_GHOST && gen->flags->terror_mode)
		*tex = gen->ghost_enemy[(*enemy)->enemy_frame];
	else if ((*enemy)->type == ENEMY_CTHULHU)
		*tex = gen->cthulhu_enemy[(*enemy)->enemy_frame];
	else if ((*enemy)->type == ENEMY_SKELETON)
		*tex = gen->skeleton_enemy[(*enemy)->enemy_frame];
	else
		return(0) ;
	return (1);
}

void	draw_enemy(t_gen *gen, int i)
{
	t_enemy		*enemy;
	t_texture	*tex;

	if (enemy_dealer(gen, &tex, &enemy, i) == 0)
		return ;
	gen->draw_enemy->sprite_x = enemy->x - gen->player->x;
	gen->draw_enemy->sprite_y = enemy->y - gen->player->y;
	gen->draw_enemy->inv_det = 1.0 / (gen->player->plane_x * gen->player->dir_y
			- gen->player->dir_x * gen->player->plane_y);
	gen->draw_enemy->transform_x = gen->draw_enemy->inv_det * (gen->player->dir_y * gen->draw_enemy->sprite_x - gen->player->dir_x
			* gen->draw_enemy->sprite_y);
	gen->draw_enemy->transform_y = gen->draw_enemy->inv_det * (-gen->player->plane_y * gen->draw_enemy->sprite_x
			+ gen->player->plane_x * gen->draw_enemy->sprite_y);
	if (gen->draw_enemy->transform_y <= 0)
		return ;
	gen->draw_enemy->sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + gen->draw_enemy->transform_x / gen->draw_enemy->transform_y));
	gen->draw_enemy->sprite_height = abs((int)(WIN_HEIGHT / gen->draw_enemy->transform_y));
	gen->draw_enemy->draw_start_y = -gen->draw_enemy->sprite_height / 2 + WIN_HEIGHT / 2;
	gen->draw_enemy->draw_end_y = gen->draw_enemy->sprite_height / 2 + WIN_HEIGHT / 2;
	if (gen->draw_enemy->draw_start_y < 0)
		gen->draw_enemy->draw_start_y = 0;
	if (gen->draw_enemy->draw_end_y >= WIN_HEIGHT)
		gen->draw_enemy->draw_end_y = WIN_HEIGHT - 1;
	gen->draw_enemy->color = 0;
	gen->draw_enemy->tex_y = 0;
	gen->draw_enemy->d = 0;
	gen->draw_enemy->sprite_width = gen->draw_enemy->sprite_height;
	gen->draw_enemy->draw_start_x = -gen->draw_enemy->sprite_width / 2 + gen->draw_enemy->sprite_screen_x;
	gen->draw_enemy->draw_end_x = gen->draw_enemy->sprite_width / 2 + gen->draw_enemy->sprite_screen_x;
	if (gen->draw_enemy->draw_start_x < 0)
		gen->draw_enemy->draw_start_x = 0;
	if (gen->draw_enemy->draw_end_x >= WIN_WIDTH)
		gen->draw_enemy->draw_end_x = WIN_WIDTH - 1;
	for (int stripe = gen->draw_enemy->draw_start_x; stripe < gen->draw_enemy->draw_end_x; stripe++)
	{
		if (gen->draw_enemy->transform_y > 0 && stripe > 0 && stripe < WIN_WIDTH
			&& gen->draw_enemy->transform_y < gen->rayhit->zbuffer[stripe])
		{
			gen->draw_enemy->tex_x = (int)((stripe - gen->draw_enemy->draw_start_x) * tex->width / (gen->draw_enemy->draw_end_x
						- gen->draw_enemy->draw_start_x));
			for (int y = gen->draw_enemy->draw_start_y; y < gen->draw_enemy->draw_end_y; y++)
			{
				gen->draw_enemy->d = y * 256 - WIN_HEIGHT * 128 + gen->draw_enemy->sprite_height * 128;
				gen->draw_enemy->tex_y = ((gen->draw_enemy->d * tex->height) / gen->draw_enemy->sprite_height) / 256;
				gen->draw_enemy->color = tex->data[gen->draw_enemy->tex_y * tex->width + gen->draw_enemy->tex_x];
				if ((gen->draw_enemy->color & 0x00FFFFFF) != 0)
				{
					if (gen->flags->terror_mode)
					{
						if (!enemy_visible(gen, &gen->draw_enemy->distance, i))
							return ;
						gen->draw_enemy->color = apply_fog(gen->draw_enemy->color, gen->draw_enemy->distance);
					}
					copied_mlx_pixel_put(gen->img_data, stripe, y, gen->draw_enemy->color);
				}
			}
		}
	}
}

void	draw_enemy_minimap(t_gen *gen, int i)
{
	int	start_x;
	int	start_y;
	int	px;
	int	py;

	start_x = (int)gen->player->x - gen->minimap->zoom_level / 2;
	start_y = (int)gen->player->y - gen->minimap->zoom_level / 2;
	px = (gen->enemy[i].x - start_x) * MINIMAP_TILE_PIXELS;
	py = (gen->enemy[i].y - start_y) * MINIMAP_TILE_PIXELS;
	if (px < 0 || py < 0 || px >= MINIMAP_PIXELS || py >= MINIMAP_PIXELS)
		return ;
	for (int y = -3; y <= 3; y++)
		for (int x = -3; x <= 3; x++)
			copied_mlx_pixel_put(gen->img_data, px + x, py + y, 0xdb27c9);
}

int	count_enemies_in_map(t_gen *gen)
{
	int	count;
	int	row;
	int	col;

	count = 0;
	row = 0;
	while (gen->parse->map[row])
	{
		col = 0;
		while (gen->parse->map[row][col])
		{
			if (gen->parse->map[row][col] == 'X'
				|| gen->parse->map[row][col] == 'x'
				|| gen->parse->map[row][col] == 'Z')
			{
				count++;
			}
			col++;
		}
		row++;
	}
	return (count);
}

void	find_enemy_from_map(t_gen *gen, int i)
{
	for (int row = 0; gen->parse->map[row]; row++)
	{
		for (int col = 0; gen->parse->map[row][col]; col++)
		{
			if (gen->parse->map[row][col] == 'X')
			{
				gen->parse->map[row][col] = '0';
				gen->enemy[i].x = col + 0.5;
				gen->enemy[i].y = row + 0.5;
				gen->enemy[i].type = ENEMY_GHOST;
				return ;
			}
			if (gen->parse->map[row][col] == 'x')
			{
				gen->parse->map[row][col] = '0';
				gen->enemy[i].x = col + 0.5;
				gen->enemy[i].y = row + 0.5;
				gen->enemy[i].type = ENEMY_CTHULHU;
				return ;
			}
			if (gen->parse->map[row][col] == 'Z')
			{
				gen->parse->map[row][col] = '0';
				gen->enemy[i].x = col + 0.5;
				gen->enemy[i].y = row + 0.5;
				gen->enemy[i].type = ENEMY_SKELETON;
				return ;
			}
		}
	}
}
