#include "../headers/cub3d.h"


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
		if (only_num(all_colors[i]) == 0)
			return (ft_free_matrix(all_colors), 0);
		rgb = ft_atoi(all_colors[i]);
		if (rgb < 0 || rgb > 255)
			return (ft_free_matrix(all_colors), 0);
		i++;
	}
	ft_free_matrix(all_colors);
	return (1);
}

char **refactored_shit(char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        {return (NULL);}
	
	if (validate_file(fd) == 0)
		{return (NULL);}
	close(fd);
	fd = open(file, O_RDONLY);
    char **matrix = ft_calloc(7, sizeof(char *));
    if (!matrix)
        return (close(fd), NULL);
    char *elements[6] = {"NO", "SO", "EA", "WE", "C", "F"};
    char *line;
    while ((line = get_next_line(fd)))
    {
        for (int i = 0; i < 6; i++)
        {
			int len;
			len = ft_strlen(elements[i]);
			if (!matrix[i] && ft_strncmp(line, elements[i], len) == 0 && line[len] == ' ')
			{
				char *final = ft_strtrim(line + len + 1, "\n");
				final = space_skipper_shift(final);
				matrix[i] = final;
			}
        }
        free(line);
    }
    close(fd);
    return matrix;
}

char	**validate_textures(char *file, t_parsing *parse)
{
	char	**matrix;
	int		i;

	matrix = refactored_shit(file);
	if (!matrix)
		return (NULL);
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

int	ultimate_file_validation(char *argv, t_parsing *parse)
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
		close(fd);
		i++;
	}
	return (1);
}
