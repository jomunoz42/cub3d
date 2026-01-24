
#include "../headers/cub3d.h"

static int	is_there_garbage(char *line)
{
	char	*tmp;
	int		i;

	tmp = ft_strtrim(line, "\n");
	i = 0;
	while (tmp[i])
	{
		if (tmp[i] != ' ' && !ft_isdigit(tmp[i]))
			return (free(tmp), 1);
		i++;
	}
	return (free(tmp), 0);
}

static int	not_one_number(char *line)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			found++;
			while (ft_isdigit(line[i]))
				i++;
			continue ;
		}
		i++;
	}
	return (found != 1);
}

static void	rgb_error_message(void)
{
	write(2, "Error\n", 6);
	write(2, "Invalid colour element\n", 24);
}

int	is_rgb_colours_invalid(char *line, char c)
{
	char	**all_colors;
	int		rgb;
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == c)
		i++;
	if (!ft_strrchr(&line[i], ','))
		return (rgb_error_message(), 1);
	all_colors = ft_split(&line[i], ',');
	if (ft_matrix_len(all_colors) != 3)
		return (free_double(all_colors), rgb_error_message(), 1);
	i = 0;
	while (i < 3)
	{
		if (is_there_garbage(all_colors[i]) || not_one_number(all_colors[i]))
			return (free_double(all_colors), rgb_error_message(), 1);
		rgb = ft_atoi(all_colors[i]);
		if (rgb < 0 || rgb > 255)
			return (free_double(all_colors), rgb_error_message(), 1);
		i++;
	}
	return (free_double(all_colors), 0);
}
