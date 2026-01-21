
#include "../headers/cub3d.h"

static int identify_header(char *line)
{
    int i;

	i = 0;
    while (line[i] == ' ')
        i++;
    if (!ft_strncmp(&line[i], "NO ", 3))
        return (E_NO);
    if (!ft_strncmp(&line[i], "SO ", 3))
        return (E_SO);
    if (!ft_strncmp(&line[i], "WE ", 3))
        return (E_WE);
    if (!ft_strncmp(&line[i], "EA ", 3))
        return (E_EA);
    if (!ft_strncmp(&line[i], "F ", 2))
        return (E_F);
    if (!ft_strncmp(&line[i], "C ", 2))
        return (E_C);
    return (-1);
}

static int is_header_line(t_parsing *data, char *line)
{
    int type;

    type = identify_header(line);
    if (type == -1)
        return (0);
    if (data->elements[type] == 1)
    {
        write(2, "Error\n", 6);
        write(2, "Invalid map, double definition of element\n", 43);
        return (-1);
    }
    data->elements[type] = 1;
    return (1);
}

static int check_all_elements(t_parsing *data)
{
    int i;

    i = 0;
    while (i < E_COUNT)
    {
        if (data->elements[i] == 0)
        {
            write(2, "Error\n", 6);
            write(2, "Invalid map, not all elements were defined\n", 44);
            return (1);
        }
        i++;
    }
    return (0);
}

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
		header = is_header_line(data, line);
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

int	not_last_element(t_parsing *data)
{
	char		*line;
	const int	fd = open(data->file_path, O_RDONLY);

	line = skip_header_and_empty_lines(data, fd);
	if (!line || check_all_elements(data))
		return (1);
	while (line)
	{
		if (is_line_empty(line))
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
	ft_bzero(data->elements, sizeof(int) * E_COUNT);
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
