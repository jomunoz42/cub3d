#include "../headers/cub3d.h"

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

char	*ft_strncpy(char *dst, char *srce, int n)
{
	unsigned char	*dest;
	unsigned char	*src;
	int				i;

	dest = (unsigned char *)dst;
	src = (unsigned char *)srce;
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return ((char *)dest);
}
