
#include "../headers/cub3d.h"

static char	*skip_header_and_empty_lines(t_parsing *data)
{
	char	*line;
	int		header;

	line = get_next_line(data->fd);
	while (line)
	{
		if (is_line_empty(line))
		{
			free(line);
			line = get_next_line(data->fd);
			continue ;
		}
		header = is_header_line_with_validation(data, line);
		if (header == 1)
		{
			free(line);
			line = get_next_line(data->fd);
			continue ;
		}
		if (header == -1)
			return (free(line), NULL);
		return (line);
	}
	write(2, "Error\nInvalid map, map not found\n", 34);
	return (NULL);
}

static char	**get_map_with_style(t_parsing *data, int count)
{
	char 	*const line = get_next_line(data->fd);
	char	**map;

	map = NULL;
	if (line != NULL)
		map = get_map_with_style(data, count + 1);
	else if (count)
	{
		map = malloc(sizeof(char *) * (count + 1));
		if (!map)
		{
			write(2, "Error\nAllocation failed\n", 25);
			return (close(data->fd), NULL); // free line???
		}
	}
	if (map)
		map[count] = line;
	return (map);
}

static void	get_height_and_max_width(t_parsing *data)
{
	int	length;

	while (data->map[data->height])
	{
		length = ft_strlen(data->map[data->height]);
		data->width = (int[]){data->width, length}[data->width < length];
		data->height++;
	}
}

int	construct_map(t_parsing *data)
{
	char		*line;

	data->textures_info = malloc(sizeof(char *) * 7);
	if (!data->textures_info)
		return (ft_free_matrix(data->textures_info), 0);
	data->textures_info[6] = NULL;

	line = skip_header_and_empty_lines(data);
	if (!line || check_all_elements(data))
		return (close(data->fd), 1);

	// for (int i = 0; i < 6; i++)
	// 	printf("VALID? right after parser: texture_info[%d]: %s\n", i, data->textures_info[i]);

	data->map = get_map_with_style(data, 1);
	if (!data->map)
		return (close(data->fd), 1);
	data->map[0] = line;
	get_height_and_max_width(data);
	return (close(data->fd), 0);
}
