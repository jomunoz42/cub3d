
#include "cub3d.h"

static int	only_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

static char	*skip_new_lines(char *line, int fd)
{
	int	no_map;

	no_map = 0;
	if (!line)
		no_map = 1;
	while (no_map == 0 && !ft_strncmp(line, "\n", 1))
	{
		free(line);
		line = get_next_line(fd);
		if (!line)
		{
			no_map = 1;
			break ;
		}
		if (only_spaces(line))
			continue ;
	}
	if (no_map == 1)
	{
		write(2, "Error\n", 6);
		write(2, "Invalid map, map not found\n", 28);
		return (NULL);
	}
	return (line);
}

static int	get_height(t_parsing *data)
{
	char	*line;
	int		fd;

	fd = open(data->file_path, O_RDONLY);
	line = get_next_line(fd);
	line = skip_new_lines(line, fd);
	if (!line)
		return (1);
	while (line)
	{
		data->height++;
		free(line);
		line = get_next_line(fd);
		if (line && !ft_strncmp(line, "\n", 1))
		{
			write(2, "Error\n", 6);
			write(2, "Invalid map, Map is not the last element in file\n", 50);
			return (free(line), 1);
		}
	}
	close(fd);
	return (0);
}

static int	construct_map(t_parsing *data) // check is file is already protected
{
	char *line;
	int length;
	int fd;
	int i;

	i = -1;
	if (get_height(data))
		return (1);
	fd = open(data->file_path, O_RDONLY);
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		(close(fd), write(2, "Error: Allocation failed\n", 25), exit(1));
	while (++i < data->height)
	{
		line = get_next_line(fd);
		line = skip_new_lines(line, fd);
		length = ft_strlen(line);
		if (data->width < length)
			data->width = length;
		data->map[i] = malloc(sizeof(char) * (length + 1));
		if (!data->map[i])
			(free(line), close(fd), write(2, "Error: Allocation failed\n", 25),
				exit(1));
		(ft_memcpy(data->map[i], line, length), free(line));
		data->map[i][length] = '\0';
	}
	data->map[i] = NULL;
	return (0);
}

static char	**create_copy(t_parsing *data)
{
	char	**map;
	int		i;

	map = malloc(sizeof(char *) * (data->height + 1));
	if (!map)
		(write(2, "Error: Allocation failed\n", 25), exit(1));
	i = -1;
	while (++i < data->height)
	{
		map[i] = malloc(sizeof(char) * (data->width + 1));
		if (!map[i])
			(write(2, "Error: Allocation failed\n", 25), exit(1));
		ft_memcpy(map[i], data->map[i], ft_strlen(data->map[i]));
		map[i][ ft_strlen(data->map[i])] = '\0';
	}
	map[i] = NULL;
	return (map);
}

int	ft_floodfill(char **map, int y, int x)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x] || map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'Z')
		return (0);
	map[y][x] = 'F';
	if (ft_floodfill(map, y + 1, x))
		return (1);
	if (ft_floodfill(map, y - 1, x))
		return (1);
	if (ft_floodfill(map, y, x + 1))
		return (1);
	if (ft_floodfill(map, y, x - 1))
		return (1);
	return (0);
}

static char	**fill_void(t_parsing *data, char **copy)
{
	int		len;
	int		x;
	int		y;

	fill_void(data, copy);
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		len = ft_strlen(data->map[y]);
		while (++x < len)
		{
			// if (data->map[y][x] == ' ')
			// realloc logic
			// Surround with a border of spaces
		}
	}
	return (0);
}

static int	is_map_valid(t_parsing *data, char **copy)
{
	int		len;
	int		x;
	int		y;

	copy = fill_void(data, copy);
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		len = ft_strlen(data->map[y]);
		while (++x < len)
		{

			// void need filment

			if (ft_floodfill(copy, x, y))
			{
				write(2, "Error\n", 6);
				write(2, "Invalid map, Map is not surrounded by walls\n", 45);
				return (free_double(copy), 1);
			}
		}
	}
	free_double(copy);
	return (0);
}

int	map_parser(t_parsing *data, char *argv)
{
	char	**copy;
	int		i;

	i = 0;
	data->file_path = argv;
	if (construct_map(data))
		return (1);
	if (construct_map(data) || find_invalid_char(data)
	 		|| find_no_player(data) || find_multiple_player(data))
		return (1);
	copy = create_copy(data);
	while (i < data->height)
	{
		printf("%s", copy[i]);
		i++;
	}
	if (is_map_valid(data, copy))
		return (1);
	return (0);
}


//     Precisa saltar as textures e as cores

//     Skip_new_lines incompleto,
//     so pode saltar das cores ao mapa  (junta varios mapas)



//   ERRORS:

//   No map found in file                     				DONE

//   Map only has spaces (no map)               			DONE

//   Map is not the last element in the file    			DONE

//   The map has 6 possible characters: 0,1,N,S,E,W,' '     DONE

//   More than one player position found       				DONE

//   No player position found              					DONE

//   Map is not surrounded by walls
