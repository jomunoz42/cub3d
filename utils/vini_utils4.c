#include "../headers/cub3d.h"

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (nptr[i] && is_space(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] && matrix)
		i++;
	return (i);
}

int	png_size_fd(const char *path, uint32_t *w, uint32_t *h)
{
	int				fd;
	ssize_t			n;
	unsigned char	buf[24];

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	n = read(fd, buf, sizeof(buf));
	close(fd);
	if (n != sizeof(buf))
		return (0);
	*w = (buf[16] << 24) | (buf[17] << 16) | (buf[18] << 8) | buf[19];
	*h = (buf[20] << 24) | (buf[21] << 16) | (buf[22] << 8) | buf[23];
	return (1);
}

int	color_switch(char *str)
{
	char	**all_colors;
	int		red;
	int		green;
	int		blue;
	int		final;

	all_colors = ft_split(str, ',');
	red = ft_atoi(all_colors[0]);
	green = ft_atoi(all_colors[1]);
	blue = ft_atoi(all_colors[2]);
	ft_free_matrix(all_colors);
	final = rgb_to_hex(red, green, blue);
	return (final);
}
