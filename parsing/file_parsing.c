#include "../headers/cub3d.h"

char	*find_texture_path(char *file, char *one_direction)
{
	t_gen *gen;

	gen = gen_stuff();
	char	*line;
	char	*path;
	int		len;

	gen->parse->fd = open(file, O_RDONLY);
	if (gen->parse->fd == -1)
		return (close(gen->parse->fd), printf("Error: can't open file\n"), NULL);
	len = ft_strlen(one_direction);
	while ((line = get_next_line(gen->parse->fd)))
	{
		if (ft_strncmp(line, one_direction, len) == 0 && line[len] == ' ')
		{
			path = ft_strtrim(line + len + 1, "\n");
			path = space_skipper_shift(path);
			free(line);
			close(gen->parse->fd);
			return (path);
		}
		free(line);
	}
	close(gen->parse->fd);
	return (NULL);
}

int	validate_rgb_colors(char *str)
{
	char	**all_colors;
	int		i;
	int		rgb;

	all_colors = ft_split(str, ',');
	if (ft_matrix_len(all_colors) != 3)
		return (ft_free_matrix(all_colors), 0);
	i = 0;
	while (i < 3)
	{
		rgb = ft_atoi(all_colors[i]);
		if (rgb < 0 || rgb > 255)
			return (ft_free_matrix(all_colors), 0);
		i++;
	}
	ft_free_matrix(all_colors);
	return (1);
}

char	**validate_textures(char *file, t_parsing *parse)
{
	char	**matrix;
	int		i;

	matrix = ft_calloc(7, sizeof(char *));
	if (!matrix)
		return (NULL);
	matrix[0] = find_texture_path(file, "NO");
	matrix[1] = find_texture_path(file, "SO");
	matrix[2] = find_texture_path(file, "WE");
	matrix[3] = find_texture_path(file, "EA");
	matrix[4] = find_texture_path(file, "F");
	matrix[5] = find_texture_path(file, "C");
	i = 0;
	while (i < 6)
	{
		if (!matrix[i])
		{
			printf("%s\n", parse->error_messages[i]);
			ft_free_matrix_partial(matrix, 7);
			return (NULL);
		}
		i++;
	}
	i = 4;
	while (i <= 5)
	{
		if (!validate_rgb_colors(matrix[i]))
		{
			printf("%s\n", parse->error_messages[i + 6]);
			ft_free_matrix_partial(matrix, 7);
			return (NULL);
		}
		i++;
	}
	return (matrix);
}

int	struct_sharingan(char *file, t_parsing *parse)
{
	char	**temp;
	int		i;
	int		len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + (len - 4), ".cub", 4))
		return (printf("Error: invalid map type\n"), 0);
	temp = validate_textures(file, parse);
	if (!temp)
		return (0);
	parse->textures_info = malloc(sizeof(char *) * 7);
	if (!parse->textures_info)
		return (ft_free_matrix(temp), 0);
	i = 0;
	while (i < 6)
	{
		parse->textures_info[i] = malloc(ft_strlen(temp[i]) + 1);
		ft_strcpy(parse->textures_info[i], temp[i]);
		i++;
	}
	ft_free_matrix(temp);
	parse->textures_info[6] = NULL;
	ft_print_matrix(parse->textures_info);
	return (1);
}

int	validate_textures_path(char *argv, t_parsing *parse)
{
	int	i;
	int	fd;

	if (struct_sharingan(argv, parse) == 0)
		return (0);
	i = 0;
	while (i <= 3)
	{
		fd = open(parse->textures_info[i], O_RDONLY);
		if (fd == -1)
			return (printf("%s\n", parse->error_messages[i + 6]), 0);
		i++;
		close(fd);
	}
	return (1);
}
