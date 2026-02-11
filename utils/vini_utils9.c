/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils9.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:40 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/11 11:02:41 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int	contains_tab(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	unc;
	size_t			a;

	unc = (unsigned char)c;
	a = 0;
	while (s[a] != '\0')
	{
		if ((unsigned char)s[a] == unc)
			return ((char *)&s[a]);
		a++;
	}
	if (unc == '\0')
		return ((char *)&s[a]);
	return (NULL);
}
