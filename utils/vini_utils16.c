/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils16.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:17:33 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/12 00:08:58 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	apply_vignette_to_image(t_gen *gen, t_img_data *img)
{
	int	x;
	int	y;

	if (!gen->flags->terror_mode)
		return ;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			apply_vignette_pixel(img, x, y);
			x++;
		}
		y++;
	}
}

char	*ft_dtoa_fixed(double v)
{
	char	*a;
	char	*b;
	char	*tmp;
	int		iv;
	int		frac;

	iv = (int)v;
	frac = (int)((v - iv) * 1000);
	if (frac < 0)
		frac = -frac;
	a = ft_itoa(iv);
	b = ft_itoa(frac);
	tmp = ft_strjoin(a, ".");
	free(a);
	a = ft_strjoin(tmp, b);
	free(tmp);
	free(b);
	return (a);
}

char	*print_helper(char *which_info, double what_to_convert)
{
	char	*num;
	char	*text;

	num = ft_dtoa_fixed(what_to_convert);
	if (!num)
		return (NULL);
	text = ft_strjoin(which_info, num);
	if (!text)
	{
		free(num);
		return (NULL);
	}
	free(num);
	return (text);
}

void	clear_image(t_img_data *img, int color)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			copied_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	calculate_player_movement(t_gen *gen)
{
	gen->player_move->move_x = 0;	
	gen->player_move->move_y = 0;	
	if (gen->kboard->key_w)
	{
		gen->player_move->move_x += gen->player->dir_x
			* gen->player->move_speed;
		gen->player_move->move_y += gen->player->dir_y
			* gen->player->move_speed;
	}
	if (gen->kboard->key_s)
	{
		gen->player_move->move_x -= gen->player->dir_x
			* gen->player->move_speed;
		gen->player_move->move_y -= gen->player->dir_y
			* gen->player->move_speed;
	}
	if (gen->kboard->key_a)
	{
		gen->player_move->move_x -= gen->player->plane_x
			* gen->player->move_speed;
		gen->player_move->move_y -= gen->player->plane_y
			* gen->player->move_speed;
	}
	if (gen->kboard->key_d)
	{
		gen->player_move->move_x += gen->player->plane_x
			* gen->player->move_speed;
		gen->player_move->move_y += gen->player->plane_y
			* gen->player->move_speed;
	}
}
