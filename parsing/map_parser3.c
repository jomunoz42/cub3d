
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

char	**get_map_with_style(int fd, int count)
{
	char	*const line = get_next_line(fd);
	char	**map;

	map = NULL;
	if (line != NULL)
		map = get_map_with_style(fd, count + 1);
	else if (count)
	{
		map = malloc(sizeof(char *) * (count + 1));
		if (!map)
		{
			write (2, "Error\nAllocation failed\n", 25);
			return (close(fd), NULL);                   // free line???
		}
	}
	if (map)
		map[count] = line;
	return (map);
}

void 	get_height_and_max_width(t_parsing *data)
{
	int			length;

	while(data->map[data->height])
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
