
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

int	not_last_element(t_parsing *data)
{
	char		*line;
	const int	fd = open(data->file_path, O_RDONLY);

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
			return (close(fd), free(line), 1);
		}
	}
	close(fd);
	return (0);
}

int	construct_map(t_parsing *data) // check is file is already protected
{
	char *line;
	int length;
	int fd;
	int i;

	i = -1;
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
	return (close(fd), 0);
}
