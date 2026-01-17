
#include "cub3d.h"

int find_invalid_char(t_parsing *data)// I am accepting F and D
{
    int     len;
    int     i;
    int     j;
    char    c;

    i = -1;
    while(++i < data->height)
    {
        j = 0;
        len = ft_strlen(data->map[i]);
        while(j < len)
        {
            c = data->map[i][j];
            if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E'
                    && c != 'W' &&  c != ' ' &&  c != 'D' && c != 'F' && c != '\n')
            {
                write (2, "Error\n", 6);
                write (2, "Invalid char in map.\n", 22);
                return (1);
            }
            j++;
        }
    }
    return (0);
}

int	find_multiple_player(t_parsing *data)
{
	int	    player_found;
	int	    i;
	int	    j;

	i = -1;
	player_found = 0;
	while (++i < data->height)
	{
		j = -1;
		while (++j < (int)ft_strlen(data->map[i]))
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
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
	int	    player_found;
    int     len;
	int	    i;
	int	    j;

	i = -1;
	player_found = 0;
	while (++i < data->height)
	{
		j = -1;
        len = ft_strlen(data->map[i]);
		while (++j < len)
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S'
				|| data->map[i][j] == 'E' || data->map[i][j] == 'W')
				player_found = 1;
		}
	}
	if (player_found == 0)
	{
		write(2, "Error\n", 6);
		write(2, "Invalid map, no player.\n", 25);
		return (1);
	}
	return (0);
}
