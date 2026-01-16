#include "../cub3d.h"

char	*find_texture_path(char *file, char *one_direction)
{
	int		fd;
	char	*line;
	char	*path;
	int		len;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error: can't open file\n"), NULL);
	len = ft_strlen(one_direction);
	while ((line = get_next_line(fd)))
	{
		if (ft_strncmp(line, one_direction, len) == 0 && line[len] == ' ')
		{
			path = ft_strtrim(line + len + 1, "\n");
			free(line);
			close(fd);
			return (path);
		}
		free(line);
	}
	close(fd);
	return (NULL);
}

int	validate_rgb_colors(char *str)
{
	char	**all_colors;
	int		i;
	int		rgb;

	all_colors = ft_split(str, ',');
	if (ft_matrix_len(all_colors) != 3)
		return (0);
	i = 0;
	while (i < 3)
	{
		rgb = ft_atoi(all_colors[i]);
		if (rgb < 0 || rgb > 255)
			return (0);
		i++;
	}
	return (1);
}

char	**validate_textures(char *file, t_parsing *parse)
{
	char	**matrix;
	int		i;

	matrix = malloc(sizeof(char *) * 7);
	if (!matrix)
		return (NULL);
	matrix[0] = find_texture_path(file, "NO");
	matrix[1] = find_texture_path(file, "SO");
	matrix[2] = find_texture_path(file, "WE");
	matrix[3] = find_texture_path(file, "EA");
	matrix[4] = find_texture_path(file, "F");
	matrix[5] = find_texture_path(file, "C");
	matrix[6] = NULL;
	i = 0;
	while (i < 6)
	{
		if (!matrix[i])
		{
			printf("%s\n", parse->error_messages[i]);
			return (NULL);
		}
		i++;
	}
	i = 4;
	while (i <= 5)
	{
		if (validate_rgb_colors(matrix[i]) == 0)
		{
			printf("%s\n", parse->error_messages[i + 6]);
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

	int len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + (len - 4), ".cub", 4))
		return (printf("Error: invalid map type\n"), 0);
	temp = validate_textures(file, parse);
	if (!temp)
		return (0);
	parse->textures_info = malloc(sizeof(char *) * 7);
	if (!parse->textures_info)
		return (0);
	i = 0;
	while (i < 6)
	{
		parse->textures_info[i] = malloc(ft_strlen(temp[i]) + 1);
		ft_strcpy(parse->textures_info[i], temp[i]);
		i++;
	}
	parse->textures_info[6] = NULL;
	ft_print_matrix(parse->textures_info);
	return (1);
}

int	validate_textures_path(char *argv, t_parsing *parse)
{
	if (struct_sharingan(argv, parse) == 0)
		return (0);
	int i = 0;
	int fd;
	while (i <= 3)
	{
		fd = open(parse->textures_info[i], O_RDONLY);
		if (fd == -1)
			return (printf("%s\n", parse->error_messages[i + 6]), 0);
		i++;
	}
	return (1);
}
