#include "../headers/cub3d.h"

void	set_player_dir(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (c == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (c == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	search_in_matrix(t_gen *gen, char c)
{
	int	row;
	int	col;

	row = 0;
	while (gen->parse->map[row])
	{
		col = 0;
		while (gen->parse->map[row][col])
		{
			if (gen->parse->map[row][col] == c)
			{
				gen->player->x = col + 0.5;
				gen->player->y = row + 0.5;
				set_player_dir(gen->player, c);
				return ;
			}
			col++;
		}
		row++;
	}
}

int	get_player_position(t_gen *gen)
{
	search_in_matrix(gen, 'N');
	search_in_matrix(gen, 'S');
	search_in_matrix(gen, 'E');
	search_in_matrix(gen, 'W');
	return (0);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_strncpy(char *dst, char *srce, int n)
{
	unsigned char	*dest;
	unsigned char	*src;
	int				i;

	dest = (unsigned char *)dst;
	src = (unsigned char *)srce;
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return ((char *)dest);
}
