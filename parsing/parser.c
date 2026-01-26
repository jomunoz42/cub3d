
#include "../headers/cub3d.h"

static int	find_invalid_char(t_parsing *data) // I am accepting F and D
{
	int len;
	int y;
	int x;
	char c;

	y = -1;
	while (++y < data->height)
	{
		x = 0;
		len = ft_strlen(data->map[y]);
		while (x < len)
		{
			c = data->map[y][x];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E'
				&& c != 'W' && c != ' ' && c != 'D' && c != 'F' && c != '\n')
			{
				write(2, "Error\n", 6);
				write(2, "Invalid char in map.\n", 22);
				return (1);
			}
			x++;
		}
	}
	return (0);
}

static int	find_multiple_player(t_parsing *data)
{
	int	player_found;
	int	y;
	int	x;

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
	int	len;
	int	y;
	int	x;

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
			{
				data->player = data->map[y][x];
				return (0);
			}
		}
	}
	if (data->player == 'Q')
		return (write(2, "Error\nInvalid map, no player.\n", 31), 1);
	return (0);
}

static int	file_parsing(t_parsing *data, int argc, char *file_path)
{
	int len;

	len = ft_strlen(file_path);
	if (argc != 2)
	{
		write(2, "Error\n", 6);
		write(2, "Incorrect number of arguments\n", 30);
		return (free(data), 1);
	}
	data->fd = open(file_path, O_RDONLY);
	if (data->fd < 0)
	{
		write(2, "Error\n", 6);
		write(2, file_path, ft_strlen(file_path));
		if (errno == ENOENT)
			return (write(2, " does not exist\n", 17), free(data), 1);
		else if (errno == EACCES)
			return (write(2, ": permission denied\n", 21), free(data), 1);
	}
	if (len < 4 || ft_strncmp(&file_path[len - 4], ".cub\0", 5))
	{
		write(2, "Error\nFile doesn't have the right extension\n", 45);
		return (close(data->fd), free(data), 1);
	}
	return (0);
}

int	parser(t_gen *gen, int argc, char **argv)
{
	gen->parse = parsing_init();
	if (!gen->parse)
		return (write(2, "Error\nAllocation failed\n", 25), 1);
	if (file_parsing(gen->parse, argc, argv[1]) != 0)
		return (1);
	if (construct_map(gen->parse))
		return (free(gen->parse), 1);
	if (find_invalid_char(gen->parse) || find_no_player(gen->parse)
		|| find_multiple_player(gen->parse) || is_map_valid(gen->parse))
		return (free_double(gen->parse->map), free(gen->parse), 1);

	int	i = -1;
	while (++i < gen->parse->height)
		printf("%s", gen->parse->map[i]);
	// free_double(gen->parse->map);
	// free(gen->parse);

	return (0);
}

// TRATAR LEAKS
