/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   picasso3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jomunoz <jomunoz@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 21:45:40 by jomunoz           #+#    #+#             */
/*   Updated: 2026/02/27 21:56:39 by jomunoz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copied_mlx_pixel_put(t_img_data *img_data, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= img_data->width || y < 0 || y >= img_data->height)
		return ;
	dest = img_data->addr + (y * img_data->line_len + x * (img_data->bits_pixel
				/ 8));
	*(unsigned int *)dest = color;
}
