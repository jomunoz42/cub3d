/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils30.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 10:39:38 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/12 10:39:40 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	load_textures(t_gen *gen, t_texture **dst, char **xpm_files, int count)
{
	int	bpp;
	int	sl;
	int	endian;
	int	i;

	i = 0;
	while (i < count)
	{
		dst[i]->img = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr,
				xpm_files[i], &dst[i]->width, &dst[i]->height);
		if (!dst[i]->img)
		{
			printf("Failed to load texture %d: %s\n", i, xpm_files[i]);
			exit(1);
		}
		dst[i]->data = (int *)mlx_get_data_addr(dst[i]->img, &bpp, &sl,
				&endian);
		i++;
	}
}
