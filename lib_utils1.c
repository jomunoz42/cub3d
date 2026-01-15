
#include "cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	a;

	a = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1[a] != '\0' || s2[a] != '\0') && a < n)
	{
		if ((unsigned char)s1[a] != (unsigned char)s2[a])
		{
			return ((unsigned char)s1[a] - (unsigned char)s2[a]);
		}
		a++;
	}
	return (0);
}

int	ft_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}
