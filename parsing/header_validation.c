
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

static int	    is_texture_path_invalid(char *line)
{
	char	*path;
	char	fd;
    int     i;

    i = 0;
    while (line[i] == ' ')
		i++;
    i += 3;
    path = ft_strtrim(&line[i], " \n");
    fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nInvalid texture: ", 24);
		write(2, path, ft_strlen(path));
		if (errno == ENOENT)
			return (write(2, " does not exist\n", 17), 1);
		else if (errno == EACCES)
			return (write(2, " has no reading permissions\n", 29), 1);
	}
	return (close(fd), 0);
}

int is_header_line_with_validation(t_parsing *data, char *line)
{
    int type;

    type = identify_header(line);
	if ((type == E_NO || type == E_SO || type == E_WE || type == E_EA) 
        && is_texture_path_invalid(line))
		return (-1);
	if (type == E_F && is_rgb_colours_invalid(line, 'F'))
		return (-1);
	if (type == E_C && is_rgb_colours_invalid(line, 'C'))
		return (-1);
    if (type == -1)
        return (0);
    if (data->elements[type] == 1)
        return (write(2, "Error\nDouble definition of element\n", 36), -1);
    data->elements[type] = 1;
    return (1);
}

int check_all_elements(t_parsing *data)
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
