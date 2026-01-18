
#include "./headers/cub3d.h"

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

size_t ft_strlen(char *str)
{
    size_t i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}