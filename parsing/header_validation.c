/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_validation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvazzs <vvazzs@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 15:11:59 by vvazzs            #+#    #+#             */
/*   Updated: 2026/02/11 15:15:39 by vvazzs           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static int	identify_header(char *line)
{
	int	i;

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

static void	write_free(char *path)
{
	write(2, "Error\nInvalid texture: ", 24);
	write(2, path, ft_strlen(path));
	free(path);
}

static int	is_texture_path_invalid(t_parsing *data, char *line, int type)
{
	char		*path;
	int			len;
	int			fd;
	static int	i;

	while (line[i] == ' ')
		i++;
	i += 3;
	path = ft_strtrim(&line[i], " \n");
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		write_free(path);
		if (errno == ENOENT)
			return (write(2, " does not exist\n", 17), 1);
		else if (errno == EACCES)
			return (write(2, " has no reading permissions\n", 29), 1);
	}
	len = ft_strlen(path);
	if (len < 4 || ft_strncmp(&path[len - 4], ".xpm\0", 5))
		return (write(2, "Error\nFile doesn't have right extension\n", 41), 1);
	if (data->textures_info[type])
		free(data->textures_info[type]);
	data->textures_info[type] = path;
	return (close(fd), 0);
}

int	is_header_line_with_validation(t_parsing *data, char *line)
{
	int	type;

	type = identify_header(line);
	if ((type == E_NO || type == E_SO || type == E_WE || type == E_EA)
		&& is_texture_path_invalid(data, line, type))
		return (-1);
	if (type == E_F && is_rgb_colours_invalid(data, line, 'F', type))
		return (-1);
	if (type == E_C && is_rgb_colours_invalid(data, line, 'C', type))
		return (-1);
	if (type == -1)
		return (0);
	if (data->elements[type] == 1)
		return (write(2, "Error\nDouble definition of element\n", 36), -1);
	data->elements[type] = 1;
	return (1);
}

int	check_all_elements(t_parsing *data, char *line)
{
	int	i;

	i = 0;
	while (i < E_COUNT)
	{
		if (data->elements[i] == 0)
		{
			write(2, "Error\n", 6);
			write(2, "Invalid map, not all elements were defined\n", 44);
			free(line);
			return (1);
		}
		i++;
	}
	return (0);
}
