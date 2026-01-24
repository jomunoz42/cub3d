
#include "../headers/cub3d.h"

static char	*skip_header_and_empty_lines(t_parsing *data, int fd)
{
	char	*line;
	int		header;

	line = get_next_line(fd);
	while (line)
	{
		if (is_line_empty(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		header = is_header_line_with_validation(data, line);
		if (header == 1)
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (header == -1)
			return (free(line), NULL);
		return (line);
	}
	write(2, "Error\nInvalid map, map not found\n", 34);
	return (NULL);
}

static char	**get_map_with_style(int fd, int count)
{
	char	**map;

	char *const line = get_next_line(fd);
	map = NULL;
	if (line != NULL)
		map = get_map_with_style(fd, count + 1);
	else if (count)
	{
		map = malloc(sizeof(char *) * (count + 1));
		if (!map)
		{
			write(2, "Error\nAllocation failed\n", 25);
			return (close(fd), NULL); // free line???
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
	const int	fd = open(data->file_path, O_RDONLY);

	line = skip_header_and_empty_lines(data, fd);
	if (!line || check_all_elements(data))
		return (1);
	data->map = get_map_with_style(fd, 1);
	if (!data->map)
		return (1);
	data->map[0] = line;
	get_height_and_max_width(data);
	return (close(fd), 0);
}
