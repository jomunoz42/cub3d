
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

int	is_header_line(char *line)
{
	int  i;

	i = 0;
	if (!line)
		return (0);
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	if (!ft_strncmp(&line[i], "NO ", 3))
		return (1);
	if (!ft_strncmp(&line[i], "SO ", 3))
		return (2);
	if (!ft_strncmp(&line[i], "WE ", 3))
		return (3);
	if (!ft_strncmp(&line[i], "EA ", 3))
		return (4);
	if (!ft_strncmp(&line[i], "F ", 2))
		return (5);
	if (!ft_strncmp(&line[i], "C ", 2))
		return (6);
	return (0);
}

static int check_double_element(t_parsing *data, char *line) // Refatorar depois
{
    int type;

	type = is_header_line(line);
    if (type == 1 && data->seen_NO++)
        return (1);
    if (type == 2 && data->seen_SO++)
        return (1);
    if (type == 3 && data->seen_WE++)
        return (1);
    if (type == 4 && data->seen_EA++)
        return (1);
    if (type == 5 && data->seen_F++)
        return (1);
    if (type == 6 && data->seen_C++)
        return (1);
    return (0);
}

static char	*skip_header_and_empty_lines(t_parsing *data, int fd)
{
	char	*line;

	(void)data;
	line = get_next_line(fd);
	while (line)
	{
		if (is_empty_line(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (is_header_line(line))
		{
			if (check_double_element(data, line))
			{
				write(2, "Error\nInvalid map, double definition of element\n", 49);
				return (free(line), NULL);
			}
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		return (line);
	}
	return (write(2, "Error\nInvalid map, map not found\n", 34), NULL);
}

int	not_last_element(t_parsing *data)
{
	char		*line;
	const int	fd = open(data->file_path, O_RDONLY);

	line = skip_header_and_empty_lines(data, fd);
	if (!line)
		return (1);
	while (line)
	{
		if (is_empty_line(line))
        {
            free(line);
            line = get_next_line(fd);
            continue;
        }
        if (is_header_line(line))
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
	if (!line)
		return (1);
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
