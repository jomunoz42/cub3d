/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_enemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:56:34 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/12 09:05:22 by vvazzs           ###   ########.fr       */
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

void	draw_enemy(t_gen *gen, int i)
{
	t_enemy		*enemy;
	t_texture	*tex;
	double		sprite_x;
	double		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			sprite_screen_x;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			color;
	int			tex_y;
	int			d;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			tex_x;
	double		distance;

	if (!gen->enemy)
		return ;
	if (gen->enemy[i].type == ENEMY_GHOST && !gen->ghost_enemy[0])
		return ;
	if (gen->enemy[i].type == ENEMY_CTHULHU && !gen->cthulhu_enemy[0] && gen->flags->terror_mode)
		return ;
	if (gen->enemy[i].type == ENEMY_SKELETON && !gen->skeleton_enemy[0])
		return ;
	enemy = &gen->enemy[i];
	if (enemy->type == ENEMY_GHOST && gen->flags->terror_mode)
		tex = gen->ghost_enemy[enemy->enemy_frame];
	else if (enemy->type == ENEMY_CTHULHU)
		tex = gen->cthulhu_enemy[enemy->enemy_frame];
	else if (enemy->type == ENEMY_SKELETON)
		tex = gen->skeleton_enemy[enemy->enemy_frame];
	else
		return ;
	sprite_x = enemy->x - gen->player->x;
	sprite_y = enemy->y - gen->player->y;
	inv_det = 1.0 / (gen->player->plane_x * gen->player->dir_y
			- gen->player->dir_x * gen->player->plane_y);
	transform_x = inv_det * (gen->player->dir_y * sprite_x - gen->player->dir_x
			* sprite_y);
	transform_y = inv_det * (-gen->player->plane_y * sprite_x
			+ gen->player->plane_x * sprite_y);
	if (transform_y <= 0)
		return ;
	sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x / transform_y));
	sprite_height = abs((int)(WIN_HEIGHT / transform_y));
	draw_start_y = -sprite_height / 2 + WIN_HEIGHT / 2;
	draw_end_y = sprite_height / 2 + WIN_HEIGHT / 2;
	if (draw_start_y < 0)
		draw_start_y = 0;
	if (draw_end_y >= WIN_HEIGHT)
		draw_end_y = WIN_HEIGHT - 1;
	color = 0;
	tex_y = 0;
	d = 0;
	sprite_width = sprite_height;
	draw_start_x = -sprite_width / 2 + sprite_screen_x;
	draw_end_x = sprite_width / 2 + sprite_screen_x;
	if (draw_start_x < 0)
		draw_start_x = 0;
	if (draw_end_x >= WIN_WIDTH)
		draw_end_x = WIN_WIDTH - 1;
	for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
	{
		if (transform_y > 0 && stripe > 0 && stripe < WIN_WIDTH
			&& transform_y < gen->rayhit->zbuffer[stripe])
		{
			tex_x = (int)((stripe - draw_start_x) * tex->width / (draw_end_x
						- draw_start_x));
			for (int y = draw_start_y; y < draw_end_y; y++)
			{
				d = y * 256 - WIN_HEIGHT * 128 + sprite_height * 128;
				tex_y = ((d * tex->height) / sprite_height) / 256;
				color = tex->data[tex_y * tex->width + tex_x];
				if ((color & 0x00FFFFFF) != 0)
				{
					if (gen->flags->terror_mode)
					{
						if (!enemy_visible(gen, &distance, i))
							return ;
						color = apply_fog(color, distance);
					}
					copied_mlx_pixel_put(gen->img_data, stripe, y, color);
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
