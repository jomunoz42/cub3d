#include "../headers/cub3d.h"

int ft_strcmp(char *s1, char *s2)
{
	int i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i])
	{
		if (s1[i] != s2[i] && s1 && s2)
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char) s1[i] - (unsigned char) s2[i]);
	return (0);
}

static int	is_set(char c, const char *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;

	if (dest == NULL && src == NULL)
		return (NULL);
	ptr = (unsigned char *)dest;
	while (n--)
		*ptr++ = *((const unsigned char *)src++);
	return (dest);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		bgn;
	int		end;
	char	*str;

	bgn = 0;
	end = ft_strlen(s1);
	if (!set || !s1)
		return (NULL);
	while (s1[bgn] && is_set(s1[bgn], set))
		bgn++;
	while (end > bgn && is_set(s1[end - 1], set))
		end--;
	str = (char *)malloc(end - bgn + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1 + bgn, end - bgn);
	str[end - bgn] = 0;
	return (str);
}

char    *ft_strcpy(char *s1, char *s2)
{
    int i;

    i = 0;
	if (!s1)
		return (NULL);
    while (s2[i])
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = s2[i]; 
    return (s1);
}

void	ft_print_matrix(char **matrix)
{
	int	indv;
	int	indh;

	if (matrix == NULL)
		return ;
	indv = -1;
	while (matrix[++indv])
	{
		indh = -1;
		while (matrix[indv][++indh])
			write(2, &matrix[indv][indh], 1);
		write(2, "\n", 1);
	}
}

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb > (size_t)-1 / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}



int	ft_str_count(char *str, char c)
{
	int	ind;
	int	count;

	count = 0;
	ind = 0;
	while (str[ind])
	{
		if (str[ind] != c && (str[ind + 1] == '\0'
				|| str[ind + 1] == c))
			count++;
		ind++;
	}
	return (count);
}

static char	*ft_split_strndup(const char *s, char c)
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

static void	*free_all(char **strs, int count)
{
	int	ind;

	ind = -1;
	while (++ind < count)
		free (strs[ind]);
	free (strs);
	return (NULL);
}

static char	**alloc_mem(int str_count)
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

static int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;
	int	sign;

	i = 0;
	result = 0;
	sign = 1;
	while (nptr[i] && is_space(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -sign;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int ft_matrix_len(char **matrix)
{
	int i = 0;
	while (matrix[i] && matrix)
		i++;
	return (i);
}

int png_size_fd(const char *path, uint32_t *w, uint32_t *h) //study this later
{
    int fd = open(path, O_RDONLY);
    if (fd < 0)
        return 0;

    unsigned char buf[24]; //why 24?
    ssize_t n = read(fd, buf, sizeof(buf));
    close(fd);
    if (n != sizeof(buf))
        return 0;
    *w = (buf[16] << 24) | (buf[17] << 16) |
         (buf[18] << 8)  |  buf[19];
    *h = (buf[20] << 24) | (buf[21] << 16) |
         (buf[22] << 8)  |  buf[23];
    return 1;
}

int color_switch(char *str)
{
	char **all_colors = ft_split(str, ',');
	int red = ft_atoi(all_colors[0]);
	int green = ft_atoi(all_colors[1]);
	int blue = ft_atoi(all_colors[2]);
	ft_free_matrix(all_colors);
	int final = rgb_to_hex(red, green, blue);
	return (final);
}

int rgb_to_hex(int r, int g, int b) //study this later
{
    return (r << 16) | (g << 8) | b;
}

char *space_skipper_shift(char *str)
{
	int i = 0;
	int j = 0;

	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;

	while (str[i])
		str[j++] = str[i++];
	str[j] = '\0';

	return str;
}

void copied_mlx_pixel_put(t_img_data *img_data, int x, int y, int color)
{
    // First, check bounds
    if (x < 0 || x >= img_data->width || y < 0 || y >= img_data->height)
        return; // outside image, do nothing

    char *dest;

    dest = img_data->addr + (y * img_data->line_len + x * (img_data->bits_pixel / 8));
    *(unsigned int *)dest = color;
}


int only_num(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

bool collision(t_gen *gen, int next_y, int next_x)
{
    return (gen->parse->map[next_y][next_x] == '1');
}

int key_press(int key, t_gen *gen)
{
    if (key == XK_Escape)
        {handle_exit(key);}

	if (key == XK_w) {gen->kboard->key_w = true;}
	if (key == XK_s) {gen->kboard->key_s = true;}
	if (key == XK_a) {gen->kboard->key_a = true;}
	if (key == XK_d) {gen->kboard->key_d = true;}
	if (key == XK_Left) {gen->kboard->key_left = true;}
	if (key == XK_Right) {gen->kboard->key_right = true;}

    return (0);
}


int key_release(int key, t_gen *gen)
{
    if (key == XK_w)
        {gen->kboard->key_w = false;}
    if (key == XK_s)
        {gen->kboard->key_s = false;}
    if (key == XK_a)
        {gen->kboard->key_a = false;}
    if (key == XK_d)
        {gen->kboard->key_d = false;}
	if (key == XK_Left)
		{gen->kboard->key_left = false;}
	if (key == XK_Right)
		{gen->kboard->key_right = false;}

    return (0);
}

void search_in_matrix(t_gen *gen, int character)
{
    int row = 0;
    if (!gen || !gen->parse || !gen->parse->map || !gen->parse->map[0][0])
        return ;
    while (gen->parse->map[row])
    {
        int col = 0;
        while (gen->parse->map[row][col])
        {
            if (gen->parse->map[row][col] == character)
            {
                gen->player->x = col + 0.5;
                gen->player->y = row + 0.5;

                gen->player->dir_x = 0;
                gen->player->dir_y = -1;
                gen->player->plane_x = 0.66;
                gen->player->plane_y = 0;
                return;
            }
            col++;
        }
        row++;
    }
}

int get_player_position(t_gen *gen)
{
    search_in_matrix(gen, 'N');
    return (0);
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}