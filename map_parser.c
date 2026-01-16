
#include "cub3d.h"

static char	*skip_new_lines(char *line, int fd)
{
	if (!line)
		return (NULL);
	while (!ft_strncmp(line, "\n", 1))
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

static void	get_height(t_parsing *data)
{
	char	*line;
	int		fd;

	fd = open(data->file_path, O_RDONLY);
	line = get_next_line(fd);
	line = skip_new_lines(line, fd);
	while (line)
	{
		data->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	construct_map(t_parsing *data) // check is file is already protected
{
	char *line;
	int length;
	int fd;
	int i;

	i = -1;
	get_height(data);
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
	}
	data->map[i] = NULL;
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
		ft_memcpy(map[i], data->map[i], data->width);
		map[i][data->width] = '\0';
	}
	map[i] = NULL;
	return (map);
}

int	ft_floodfill(char **map, int y, int x)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x] || map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'F')
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

// int find_invalid_char(t_parsing *data)//check if another char might be valid
// {
//     char    c;
//     int     i;
//     int     j;

//     i = -1;
//     while(++i < data->height)
//     {
//         j = 0;
//         while(j < data->width)
//         {
//             c = data->map[i][j];
//             if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E'
//                     && c != 'W' && c != ' ')
//             {
//                 write (2, "Error\n", 6);
//                 write (2, "Invalid char in map.\n", 22);
//                 return (1);
//             }
//             j++;
//         }
//     }
//     return (0);
// }

int	find_multiple_player(t_parsing *data)
{
	int	player_found;
	int	i;
	int	j;

	i = -1;
	player_found = 0;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
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
	int	player_found;
	int	i;
	int	j;

	i = -1;
	player_found = 0;
	while (++i < data->height)
	{
		j = -1;
		while (++j < data->width)
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

int	map_parser(t_parsing *data, char *argv)
{
	char	**copy;
	int		i;

	i = 0;
	data->file_path = argv;
	construct_map(data);
	if (/* find_invalid_char(data) ||*/ find_no_player(data)
		|| find_multiple_player(data))
		return (1);
	copy = create_copy(data);
	while (i < data->height)
	{
		printf("%s", copy[i]);
		i++;
	}
	return (0);
}                       //  final do dia deu cagada no mapa

//     Error\n

//     Precisa saltar as textures e as cores

//     Skip_new_lines incompleto,
//     so pode saltar das cores ao mapa  (junta varios mapas)

//     Implementar floodfill em tudo o que e mapa (nao 1) que esta adjacente em espaco

//   ERRORS:

//   No map found in file

//   Map is not the last element in the file

//   The map must be composed of only 6 possible characters: 0,1,N,S,E,W,' '      DONE

//   More than one player position found        DONE

//   No player position found               DONE

//   Map is not surrounded by walls
//   Hole in the map
//   Open map (leak to outside)
//   Walkable tile touching the void
//   Walkable cell next to a space

//   Map has zero valid lines
// (Spaces are a valid part of the map but a file of only spaces/newlines
// is not a valid map)