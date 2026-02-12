/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils16.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:17:33 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/12 09:06:52 by vvazzs           ###   ########.fr       */
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

static void	apply_move(t_player_move *move, double dir_x, double dir_y,
		double speed)
{
	move->move_x += dir_x * speed;
	move->move_y += dir_y * speed;
}

void	calculate_player_movement(t_gen *gen)
{
	t_player	*p;

	p = gen->player;
	gen->player_move->move_x = 0;
	gen->player_move->move_y = 0;
	if (gen->kboard->key_w)
		apply_move(gen->player_move, p->dir_x, p->dir_y, p->move_speed);
	if (gen->kboard->key_s)
		apply_move(gen->player_move, p->dir_x, p->dir_y, -p->move_speed);
	if (gen->kboard->key_a)
		apply_move(gen->player_move, p->plane_x, p->plane_y, -p->move_speed);
	if (gen->kboard->key_d)
		apply_move(gen->player_move, p->plane_x, p->plane_y, p->move_speed);
}
