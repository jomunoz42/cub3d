/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vini_utils7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 11:02:36 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/11 11:02:37 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

char	*ft_strcat(char *dst, char *srce)
{
	unsigned char	*dest;
	unsigned char	*src;
	int				i;
	int				j;

	dest = (unsigned char *)dst;
	src = (unsigned char *)srce;
	i = ft_strlen(dst);
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return ((char *)dest);
}

int	png_name_to_xpm(t_gen *gen, char *xpm_files[4])
{
	char	*name;
	char	*dot;
	int		len;
	int		i;

	i = 0;
	while (i < 4)
	{
		name = gen->parse->textures_info[i];
		if (!name)
			return (0);
		dot = strrchr(name, '.');
		if (dot)
			len = (int)(dot - name);
		else
			len = (int)strlen(name);
		xpm_files[i] = malloc(len + ft_strlen(".xpm") + 1);
		if (!xpm_files[i])
			return (0);
		ft_strncpy(xpm_files[i], name, len);
		xpm_files[i][len] = '\0';
		ft_strcat(xpm_files[i], ".xpm");
		i++;
	}
	return (1);
}

size_t	ft_putnbr_fake(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	digits;
	size_t	i;
	char	*str;
	long	num;

	num = n;
	digits = ft_putnbr_fake(n);
	str = (char *)malloc(digits + 1);
	if (!str)
		return (NULL);
	str[digits] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	i = digits - 1;
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[i--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = (char *)malloc(i + j + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, i);
	ft_memcpy(str + i, s2, j);
	str[i + j] = '\0';
	return (str);
}
