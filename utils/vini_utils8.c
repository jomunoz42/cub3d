#include "../headers/cub3d.h"

int	ft_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

t_texture	*load_xpm_texture(void *mlx_ptr, char *file)
{
	t_texture	*tex;

	tex = malloc(sizeof(t_texture));
	if (!tex)
		return (NULL);
	tex->img = mlx_xpm_file_to_image(mlx_ptr, file, &tex->width, &tex->height);
	if (!tex->img)
	{
		free(tex);
		return (NULL);
	}
	tex->data = (int *)mlx_get_data_addr(tex->img, &(int){0}, &(int){0},
			&(int){0});
	return (tex);
}

void	open_close_door(t_gen *gen)
{
	double		ray_x;
	double		ray_y;
	t_rayhit	hit;
	char		*cell;

	ray_x = gen->player->dir_x;
	ray_y = gen->player->dir_y;
	hit = castrate(gen, ray_x, ray_y, 1);
	if (hit.type != HIT_DOOR)
		return ;
	if (hit.dist > 1.5)
		return ;
	cell = &gen->parse->map[hit.map_y][hit.map_x];
	if (*cell == 'D')
		*cell = 'd';
	else if (*cell == 'd')
		*cell = 'D';
}

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)b;
	while (i < len)
		ptr[i++] = (unsigned char)c;
	return (b);
}
