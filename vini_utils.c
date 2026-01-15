#include "cub3d.h"

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i])
	{
		if (s1[i] != s2[i] && s1 && s2)
			return (0);
		i++;
	}
	return (1);
}