#include "../headers/cub3d.h"

int	rgb_to_hex(int r, int g, int b) // study this later
{
	return ((r << 16) | (g << 8) | b);
}

char	*space_skipper_shift(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
		str[j++] = str[i++];
	str[j] = '\0';
	return (str);
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

int	only_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}
