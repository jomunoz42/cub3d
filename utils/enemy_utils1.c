/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vivaz-ca <vivaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 09:46:09 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/16 18:54:46 by vivaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	draw_enemy_variable_initialization(t_gen *gen, t_enemy *enemy)
{
	gen->draw_enemy->sprite_x = enemy->x - gen->player->x;
	gen->draw_enemy->sprite_y = enemy->y - gen->player->y;
	gen->draw_enemy->inv_det = 1.0 / (gen->player->plane_x * gen->player->dir_y
			- gen->player->dir_x * gen->player->plane_y);
	gen->draw_enemy->transform_x = gen->draw_enemy->inv_det
		* (gen->player->dir_y * gen->draw_enemy->sprite_x - gen->player->dir_x
			* gen->draw_enemy->sprite_y);
	gen->draw_enemy->transform_y = gen->draw_enemy->inv_det
		* (-gen->player->plane_y * gen->draw_enemy->sprite_x
			+ gen->player->plane_x * gen->draw_enemy->sprite_y);
}

void	crazy_math_operations(t_gen *gen)
{
	gen->draw_enemy->sprite_screen_x = (int)((WIN_WIDTH / 2) * (1
				+ gen->draw_enemy->transform_x / gen->draw_enemy->transform_y));
	gen->draw_enemy->sprite_height = abs((int)(WIN_HEIGHT
				/ gen->draw_enemy->transform_y));
	gen->draw_enemy->draw_start_y = -gen->draw_enemy->sprite_height / 2
		+ WIN_HEIGHT / 2;
	gen->draw_enemy->draw_end_y = gen->draw_enemy->sprite_height / 2
		+ WIN_HEIGHT / 2;
	if (gen->draw_enemy->draw_start_y < 0)
		gen->draw_enemy->draw_start_y = 0;
	if (gen->draw_enemy->draw_end_y >= WIN_HEIGHT)
		gen->draw_enemy->draw_end_y = WIN_HEIGHT - 1;
	gen->draw_enemy->color = 0;
	gen->draw_enemy->tex_y = 0;
	gen->draw_enemy->d = 0;
	gen->draw_enemy->sprite_width = gen->draw_enemy->sprite_height;
	gen->draw_enemy->draw_start_x = -gen->draw_enemy->sprite_width / 2
		+ gen->draw_enemy->sprite_screen_x;
	gen->draw_enemy->draw_end_x = gen->draw_enemy->sprite_width / 2
		+ gen->draw_enemy->sprite_screen_x;
	if (gen->draw_enemy->draw_start_x < 0)
		gen->draw_enemy->draw_start_x = 0;
	if (gen->draw_enemy->draw_end_x >= WIN_WIDTH)
		gen->draw_enemy->draw_end_x = WIN_WIDTH - 1;
}

void	render_enemy_stripe(t_gen *gen, t_texture *tex, int stripe)
{
	int	y;

	gen->draw_enemy->tex_x = (int)((stripe - gen->draw_enemy->draw_start_x)
			* tex->width / (gen->draw_enemy->draw_end_x
				- gen->draw_enemy->draw_start_x));
	y = gen->draw_enemy->draw_start_y;
	while (y < gen->draw_enemy->draw_end_y)
	{
		gen->draw_enemy->d = y * 256 - WIN_HEIGHT * 128
			+ gen->draw_enemy->sprite_height * 128;
		gen->draw_enemy->tex_y = ((gen->draw_enemy->d * tex->height)
				/ gen->draw_enemy->sprite_height) / 256;
		gen->draw_enemy->color = tex->data[gen->draw_enemy->tex_y * tex->width
			+ gen->draw_enemy->tex_x];
		if ((gen->draw_enemy->color & 0x00FFFFFF) != 0)
		{
			if (gen->flags->terror_mode)
				gen->draw_enemy->color = apply_fog(gen->draw_enemy->color,
						gen->draw_enemy->distance);
			copied_mlx_pixel_put(gen->img_data, stripe, y,
				gen->draw_enemy->color);
		}
		y++;
	}
}

void	draw_enemy_square(t_gen *gen, int px, int py)
{
	int	x;
	int	y;

	y = -3;
	while (y <= 3)
	{
		x = -3;
		while (x <= 3)
		{
			copied_mlx_pixel_put(gen->img_data, px + x, py + y, 0xdb27c9);
			x++;
		}
		y++;
	}
}
