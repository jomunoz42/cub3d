/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_new_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:39:19 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/27 23:25:11 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	texture_data_init(t_gen *gen)
{
	gen->texture_data = malloc(sizeof(t_texture_data));
	if (!gen->texture_data)
		return (0);
	gen->texture_data->clng_color = color_switch(gen->parse->textures_info[5]);
	gen->texture_data->flr_color = color_switch(gen->parse->textures_info[4]);
	gen->texture_data->horizon = gen->mlx_data->win_height / 2;
	return (1);
}

int	minimap_init(t_gen *gen)
{
	gen->minimap = malloc(sizeof(t_minimap));
	if (!gen->minimap)
		return (0);
	gen->minimap->map = NULL;
	gen->minimap->width = gen->mlx_data->win_width * 0.20;
	gen->minimap->height = gen->mlx_data->win_height * 0.20;
	gen->minimap->image.img = mlx_new_image(gen->mlx_data->mlx_ptr,
			gen->minimap->width, gen->minimap->height);
	gen->minimap->image.addr = mlx_get_data_addr(gen->minimap->image.img,
			&gen->minimap->image.bits_pixel, &gen->minimap->image.line_len,
			&gen->minimap->image.endian);
	gen->minimap->image.height = gen->mlx_data->win_height;
	gen->minimap->image.width = gen->mlx_data->win_width;
	gen->minimap->zoom_level = 14.0;
	return (1);
}

int	keyboard_init(t_gen *gen)
{
	gen->kboard = malloc(sizeof(t_keyboard));
	if (!gen->kboard)
		return (0);
	gen->kboard->key_w = false;
	gen->kboard->key_a = false;
	gen->kboard->key_s = false;
	gen->kboard->key_d = false;
	gen->kboard->key_e = false;
	gen->kboard->space = false;
	gen->kboard->key_right = false;
	gen->kboard->key_left = false;
	gen->kboard->control_left = false;
	gen->kboard->shift_left = false;
	gen->kboard->key_f = false;
	gen->kboard->key_l = false;
	gen->kboard->key_i = false;
	gen->kboard->key_caps_lock = false;
	gen->kboard->key_z = false;
	gen->kboard->key_x = false;
	gen->kboard->key_m = false;
	return (1);
}

int	rayhit_init(t_gen *gen)
{
	gen->rayhit = malloc(sizeof(t_rayhit));
	if (!gen->rayhit)
		return (0);
	gen->rayhit->dist = 0;
	gen->rayhit->map_x = 0;
	gen->rayhit->map_y = 0;
	gen->rayhit->side = -1;
	ft_memset(gen->rayhit->zbuffer, 0, sizeof(gen->rayhit->zbuffer));
	return (1);
}
