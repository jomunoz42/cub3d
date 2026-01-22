
#include "./headers/cub3d.h"

void	free_double(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i])
		free(arg[i++]);
	free(arg);
	return ;
}

int	is_line_empty(char *line)
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

char	*ft_strdup(const char *s)
{
	char	*str;
	int		a;
	int		size;

	size = ft_strlen(s);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	a = 0;
	while (a < size)
	{
		str[a] = s[a];
		a++;
	}
	str[a] = '\0';
	return (str);
}
