#include "../headers/cub3d.h"

int	apply_fog(int color, double dist)
{
	double	factor;
	int		r;
	int		g;
	int		b;

	if (dist <= FOG_START)
		return (color);
	if (dist >= FOG_END)
		return (0x000000);
	factor = 1.0 - (dist - FOG_START) / (FOG_END - FOG_START);
	r = ((color >> 16) & 0xFF) * factor;
	g = ((color >> 8) & 0xFF) * factor;
	b = (color & 0xFF) * factor;
	return ((r << 16) | (g << 8) | b);
}

char	*ft_split_strndup(const char *s, char c)
{
	char	*src;
	char	*dest;
	int		size;

	size = 0;
	while (s[size])
	{
		if (s[size] == c)
			break ;
		size++;
	}
	if (s == NULL)
		return (NULL);
	src = (char *)s;
	dest = ft_calloc(size + 1, 1);
	if (dest == NULL)
		return (NULL);
	ft_bzero(dest, size + 1);
	dest = ft_memcpy(dest, src, size);
	return (dest);
}

void	*free_all(char **strs, int count)
{
	int	ind;

	ind = -1;
	while (++ind < count)
		free(strs[ind]);
	free(strs);
	return (NULL);
}

char	**alloc_mem(int str_count)
{
	char	**ret;

	ret = malloc((str_count + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	ret[str_count] = NULL;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	char	*str;
	int		str_count;
	int		indv;

	if (s == NULL)
		return (NULL);
	indv = 0;
	str = (char *)s;
	str_count = ft_str_count(str, c);
	ret = alloc_mem(str_count);
	if (ret == NULL)
		return (NULL);
	while (str_count-- > 0)
	{
		while (*str == c && *str)
			str++;
		ret[indv] = ft_split_strndup(str, c);
		if (ret[indv] == NULL && indv != str_count)
			return (free_all(ret, indv));
		indv++;
		while (*str != c && *str)
			str++;
	}
	return (ret);
}
