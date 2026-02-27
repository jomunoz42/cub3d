/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 14:31:30 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/27 23:22:04 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_pixel_color_img(t_img_data *img, int x, int y)
{
	char	*pixel;

	if (!img || !img->addr)
		return (0);
	if (x < 0 || x >= img->line_len / (img->bits_pixel / 8) || y < 0)
		return (0);
	pixel = img->addr + y * img->line_len + x * (img->bits_pixel / 8);
	return (*(int *)pixel);
}

void	copied_mlx_pixel_put(t_img_data *img_data, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= img_data->width || y < 0 || y >= img_data->height)
		return ;
	dest = img_data->addr + (y * img_data->line_len + x * (img_data->bits_pixel
				/ 8));
	*(unsigned int *)dest = color;
}
