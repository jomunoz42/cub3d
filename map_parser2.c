
#include "cub3d.h"

int find_invalid_char(t_parsing *data)// I am accepting F and D
{
    int     len;
    int     y;
    int     x;
    char    c;

    y = -1;
    while(++y < data->height)
    {
        x = 0;
        len = ft_strlen(data->map[y]);
        while(x < len)
        {
            c = data->map[y][x];
            if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E'
                    && c != 'W' &&  c != ' ' &&  c != 'D' && c != 'F' && c != '\n')
            {
                write (2, "Error\n", 6);
                write (2, "Invalid char in map.\n", 22);
                return (1);
            }
            x++;
        }
    }
    return (0);
}

int	find_multiple_player(t_parsing *data)
{
	int	    player_found;
	int	    y;
	int	    x;

	y = -1;
	player_found = 0;
	while (++y < data->height)
	{
		x = -1;
		while (++x < (int)ft_strlen(data->map[y]))
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				if (player_found == 1)
				{
					write(2, "Error\n", 6);
					write(2, "Invalid map, more than 1 player.\n", 34);
					return (1);
				}
				player_found = 1;
			}
		}
	}
	return (0);
}

int	find_no_player(t_parsing *data)
{
    int     len;
	int	    y;
	int	    x;

	y = -1;
	data->player = 'Q';
	while (++y < data->height)
	{
		x = -1;
        len = ft_strlen(data->map[y]);
		while (++x < len)
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
				data->player = data->map[y][x];
		}
	}
	if (data->player == 'Q')
	{
		write(2, "Error\n", 6);
		write(2, "Invalid map, no player.\n", 25);
		return (1);
	}
	return (0);
}
