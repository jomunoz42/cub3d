
#include "../headers/cub3d.h"

static int find_invalid_char(t_parsing *data)// I am accepting F and D
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

static int	find_multiple_player(t_parsing *data)
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

static int	find_no_player(t_parsing *data)
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

static int	file_parsing(int argc, char *file_path)
{
	int	fd;

	if (argc != 2)
	{
		write(2, "Error\n", 6);
		write(2, "Incorrect number of arguments\n", 31);
		return (1);
	}
	fd = open(file_path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\n", 6);
		write(2, file_path, ft_strlen(file_path));
		if (errno == ENOENT)
			return (write(2, " does not exist\n", 17), 1);
		else if (errno == EACCES)
			return (write(2, " has no reading permissions\n", 29), 1);
	}
	return (close(fd), 0);
}

int	parser(t_gen *gen, int argc, char **argv)
{
	if (file_parsing(argc, argv[1]) != 0)
		return (1);
    gen->parse = parsing_init();
    if (!gen->parse)
		return (write (2, "Error\nAllocation failed\n", 25), 1);
	gen->parse->file_path = argv[1];
	if (construct_map(gen->parse) 
		|| find_invalid_char(gen->parse)
		|| find_no_player(gen->parse) 
		|| find_multiple_player(gen->parse)
		|| is_map_valid(gen->parse))
		return (1);
	
	int	i = -1;
	while(++i < gen->parse->height)
		printf("%s", gen->parse->map[i]);
	// free_double(gen->parse->map);
	return (0);
}
 



//      png not valid???????????????????????

//      I AM ACCEPTING TABS

//      REVIEW AND FFEDBACK