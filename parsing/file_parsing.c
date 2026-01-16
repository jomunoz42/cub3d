#include "../cub3d.h"

char	*validate_texture_path(char *file, char *one_direction)
{
	int		fd;
	char	*line;
	char	*path;
	int		len;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error when opening the file\n"), NULL);
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

char	**validate_textures(char *file)
{
	char **matrix; // mudar nome quando tiver uma ideia mais legal
	matrix = malloc(sizeof(char *) * 7);
	if (!matrix)
		return (NULL);
	matrix[0] = validate_texture_path(file, "NO");
	matrix[1] = validate_texture_path(file, "SO");
	matrix[2] = validate_texture_path(file, "WE");
	matrix[3] = validate_texture_path(file, "EA");
	matrix[4] = validate_texture_path(file, "F");
	matrix[5] = validate_texture_path(file, "C");
	matrix[6] = NULL;
	if (!matrix[0] || !matrix[1] || !matrix[2] || !matrix[3] || !matrix[4]
		|| !matrix[5])
	{
		printf("Error: missing texture or color\n");
		return (NULL);
	}
	if (validate_rgb_colors(matrix[4]) == 0
		|| validate_rgb_colors(matrix[5]) == 0)
	{
		printf("Error: cor invalida\n");
		return (NULL);
	}
	return (matrix);
}

void	get_texture_info(char *file, t_parsing *parse)
{
	char	**temp;
	int		i;

	temp = validate_textures(file);
	if (!temp)
		return ;
	parse->textures_info = malloc(sizeof(char *) * 7);
	if (!parse->textures_info)
		return ;
	i = 0;
	while (i < 6)
	{
		parse->textures_info[i] = malloc(ft_strlen(temp[i]) + 1);
		ft_strcpy(parse->textures_info[i], temp[i]);
		i++;
	}
	parse->textures_info[6] = NULL;
	ft_print_matrix(parse->textures_info);
}
