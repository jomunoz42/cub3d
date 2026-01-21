
#include "../headers/cub3d.h"

static int	ft_floodfill(char **map, int y, int x)
{
	if (y < 0 || x < 0 || !map[y] || !map[y][x] || map[y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == 'Z')
		return (0);
	map[y][x] = 'Z';
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

static char	**create_copy_map(t_parsing *data)
{
	char	**copy;
	int		i;
	int		j;

	copy = malloc(sizeof(char *) * (data->height + 1));
	if (!copy)
		(write(2, "Error: Allocation failed\n", 25), exit(1));
	i = -1;
	while (++i < data->height)
	{
		copy[i] = malloc(sizeof(char) * (data->width + 1));
		if (!copy[i])
			(write(2, "Error: Allocation failed\n", 25), exit(1));
		j = 0;
		while (j < data->width)
			copy[i][j++] = ' ';
		ft_memcpy(copy[i], data->map[i], ft_strlen(data->map[i]));
		copy[i][data->width] = '\0';
	}
	copy[i] = NULL;
	return (copy);
}

static int	is_map_valid(t_parsing *data)
{
	char	**copy;
	int		y;
	int		x;

	copy = create_copy_map(data);
	y = -1;
	while (++y < data->height)
	{
		x = -1;
		while (++x < data->width)
		{
			if (copy[y][x] == '0' || copy[y][x] == data->player)
			{
				if (ft_floodfill(copy, y, x))
				{
					write(2, "Error\n", 6);
					return (write(2, "Invalid map, not surrounded by walls.\n",
							39), 1);
				}
			}
		}
	}
	return (free_double(copy), 0);
}

int	map_parser(t_parsing *data, char *argv)
{
	data->file_path = argv;
	ft_bzero(data->elements, sizeof(int) * E_COUNT);
	if (not_last_element(data) || construct_map(data) || find_invalid_char(data)
		|| find_no_player(data) || find_multiple_player(data)
		|| is_map_valid(data))
		return (1);
	int i = 0;
	while(i < data->height)
	{
		printf("%s", data->map[i]);
		i++;
	}
	// free_double(data->map);
	return (0);
}


// 11111111 1111111 111111111111   1








// 1

// NOT COUNTING THAT AS MAP



//int	is_header_line(char *line)  // it can have spaces before




// is one of the six missing?


//    ver se tem todos os elementos

// 


//   ERRORS:


//   Double defenition of element

//   Not all elements were defined


//   No map found in file                     				DONE

//   Map only has spaces (no map)               			DONE

//   Map is not the last element in the file    			DONE

//   The map has 6 possible characters: 0,1,N,S,E,W,' '     DONE

//   More than one player position found       				DONE

//   No player position found              					DONE

//   Map is not surrounded by walls                         DONE
 