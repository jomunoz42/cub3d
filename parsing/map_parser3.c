
#include "../headers/cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	is_header_line(t_parsing *data, char *line)  // it can have spaces before
{
	int  i;

	i = 0;
	if (!line)
		return (0);
	while(line[i] == ' ')
		i++;
	if (!ft_strncmp(&line[i], "NO ", 3))
	{
		data->seen_NO++;
		return (1);
	}
	if (!ft_strncmp(&line[i], "SO ", 3))
	{
		data->seen_SO++;
		return (1);
	}
	if (!ft_strncmp(&line[i], "WE ", 3))
	{
		data->seen_WE++;
		return (1);
	}
	if (!ft_strncmp(&line[i], "EA ", 3))
	{
		data->seen_EA++;
		return (1);
	}
	if (!ft_strncmp(&line[i], "F ", 2))
	{
		data->seen_F++;
		return (1);
	}
	if (!ft_strncmp(&line[i], "C ", 2))
	{
		data->seen_C++;
		return (1);
	}
	return (0);
}

static int	check_element_number(t_parsing *data)
{
	if (data->seen_WE > 1 || data->seen_SO > 1 || data->seen_NO > 1
	    || data->seen_EA > 1 || data->seen_F > 1 || data->seen_C > 1)
	{
		write(2, "Error\n", 6);
		write(2, "Invalid map, double defenition of element\n", 43);
		return (1);
	}
	if (data->seen_WE < 1 || data->seen_SO < 1 || data->seen_NO < 1
	    || data->seen_EA < 1 || data->seen_F < 1 || data->seen_C < 1)
	{
		write(2, "Error\n", 6);
		write(2, "Invalid map, not all elements were defined\n", 44);
		return (1);
	}
	return (0);
}

static char	*skip_header_and_empty_lines(t_parsing *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_header_line(data, line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		return (line);
	}
	write(2, "Error\nInvalid map, map not found\n", 34);
	return (NULL);
}

int	not_last_element(t_parsing *data)
{
	char		*line;
	const int	fd = open(data->file_path, O_RDONLY);

	line = skip_header_and_empty_lines(data, fd);
	if (!line)
		return (1);
	if (check_element_number(data))
			return (1);
	while (line)
	{
		if (is_empty_line(line))
        {
            free(line);
            line = get_next_line(fd);
            continue;
        }
        if (is_header_line(data, line))
        {
            write(2, "Error\n", 6);
            write(2, "Invalid map, map is not the last element in file\n", 50);
            return (free(line), close(fd), 1);
        }
		data->height++;
		free(line);
		line = get_next_line(fd);
	}
	return (close(fd), 0);
}

int	construct_map(t_parsing *data)
{
	char		*line;
	int			length;
	int			i;
	const int	fd = open(data->file_path, O_RDONLY);

	i = -1;
	line = skip_header_and_empty_lines(data, fd);
	data->map = malloc(sizeof(char *) * (data->height + 1));
	if (!data->map)
		(close(fd), write(2, "Error: Allocation failed\n", 25), exit(1));
	while (++i < data->height)
	{
		if (i > 0)
			line = get_next_line(fd);
		length = ft_strlen(line);
		if (data->width < length)
			data->width = length;
		data->map[i] = malloc(sizeof(char) * (length + 1));
		if (!data->map[i])
			(free(line), close(fd), write(2, "Error: Allocation failed\n",
					25), exit(1));
		(ft_memcpy(data->map[i], line, length), free(line));
		data->map[i][length] = '\0';
	}
	data->map[i] = NULL;
	return (close(fd), 0);
}
