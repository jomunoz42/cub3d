#include "../headers/cub3d.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
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
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

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
		if (str[ind] != c && (str[ind + 1] == '\0' || str[ind + 1] == c))
			count++;
		ind++;
	}
	return (count);
}

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
		free(strs[ind]);
	free(strs);
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

int	ft_matrix_len(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i] && matrix)
		i++;
	return (i);
}

int	png_size_fd(const char *path, uint32_t *w, uint32_t *h) // study this later
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);

	unsigned char buf[24]; // why 24?
	ssize_t n = read(fd, buf, sizeof(buf));
	close(fd);
	if (n != sizeof(buf))
		return (0);
	*w = (buf[16] << 24) | (buf[17] << 16) | (buf[18] << 8) | buf[19];
	*h = (buf[20] << 24) | (buf[21] << 16) | (buf[22] << 8) | buf[23];
	return (1);
}

int	color_switch(char *str)
{
	char	**all_colors;
	int		red;
	int		green;
	int		blue;
	int		final;

	all_colors = ft_split(str, ',');
	red = ft_atoi(all_colors[0]);
	green = ft_atoi(all_colors[1]);
	blue = ft_atoi(all_colors[2]);
	ft_free_matrix(all_colors);
	final = rgb_to_hex(red, green, blue);
	return (final);
}

int	rgb_to_hex(int r, int g, int b) // study this later
{
	return ((r << 16) | (g << 8) | b);
}

char	*space_skipper_shift(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
		str[j++] = str[i++];
	str[j] = '\0';
	return (str);
}

void	copied_mlx_pixel_put(t_img_data *img_data, int x, int y, int color)
{
	char	*dest;

	if (x < 0 || x >= img_data->width || y < 0 || y >= img_data->height)
		return ;
	dest = img_data->addr + (y * img_data->line_len + x * (img_data->bits_pixel
				/ 8));
	*(unsigned int *)dest = color;
}

int	only_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

bool	collision(t_gen *gen, double next_y, double next_x)
{
	int		map_y;
	int		map_x;
	double	radius;
	int		top;
	int		bottom;
	int		left;
	int		right;

	map_y = (int)next_y;
	map_x = (int)next_x;
	if (map_y < 0 || map_y >= gen->parse->height)
		return (true);
	if (map_x < 0 || map_x >= (int)ft_strlen(gen->parse->map[map_y]))
		return (true);
	radius = 0.2;
	top = (int)(next_y - radius);
	bottom = (int)(next_y + radius);
	left = (int)(next_x - radius);
	right = (int)(next_x + radius);
	if (top >= 0 && top < gen->parse->height && left >= 0
		&& left < (int)ft_strlen(gen->parse->map[top])
		&& gen->parse->map[top][left] == '1')
		return (true);
	if (top >= 0 && top < gen->parse->height && right >= 0
		&& right < (int)ft_strlen(gen->parse->map[top])
		&& gen->parse->map[top][right] == '1')
		return (true);
	if (bottom >= 0 && bottom < gen->parse->height && left >= 0
		&& left < (int)ft_strlen(gen->parse->map[bottom])
		&& gen->parse->map[bottom][left] == '1')
		return (true);
	if (bottom >= 0 && bottom < gen->parse->height && right >= 0
		&& right < (int)ft_strlen(gen->parse->map[bottom])
		&& gen->parse->map[bottom][right] == '1')
		return (true);
	return (false);
}

int	key_press(int key, t_gen *gen)
{
		const char *audio_files[5] = {"./audio/default1.mp3",
			"./audio/default2.mp3", "./audio/default3.mp3",
			"./audio/default4.mp3", "./audio/default5.mp3"};
	int	index;

	if (key == XK_Escape)
	{
		handle_exit(key);
	}
	if (key == XK_w)
	{
		gen->kboard->key_w = true;
	}
	if (key == XK_s)
	{
		gen->kboard->key_s = true;
	}
	if (key == XK_a)
	{
		gen->kboard->key_a = true;
	}
	if (key == XK_d)
	{
		gen->kboard->key_d = true;
	}
	if (key == XK_Left)
	{
		gen->kboard->key_left = true;
	}
	if (key == XK_Right)
	{
		gen->kboard->key_right = true;
	}
	if (key == XK_Control_L)
	{
		gen->kboard->control_left = true;
		if (gen->flags->terror_mode)
		{
			gen->player->move_speed = gen->def_values->terror_player_move_speed
				/* + 0.03 */;
			gen->enemy->move_speed = gen->player->move_speed - 0.01;
		}
		else
		{
			gen->player->move_speed = gen->def_values->player_move_speed + 0.06;
			gen->player->rotate_speed = 0.060;
			gen->player->fov += 0.07;
		}
	}
	if (key == XK_Shift_L)
	{
		gen->kboard->shift_left = true;
		gen->player->move_speed = 0.01;
		gen->player->rotate_speed = 0.030;
	}
	if (key == XK_f)
	{
		gen->kboard->key_f = true;
		gen->player->fov -= 0.01;
	}
	if (key == XK_l)
	{
		gen->kboard->key_l = true;
		gen->player->fov += 0.01;
	}
	if (key == XK_z)
	{
		gen->kboard->key_z = true;
		gen->minimap->zoom_level -= 0.5;
	}
	if (key == XK_x)
	{
		gen->kboard->key_x = true;
		gen->minimap->zoom_level += 0.5;
	}
	if (key == XK_r)
	{
		gen->player->fov = gen->def_values->fov;
		gen->minimap->zoom_level = gen->def_values->minimap_zoom_level;
	}
	if (key == XK_t && !gen->kboard->key_t)
	{
		gen->kboard->key_t = true;
		stop_all_sounds(gen);
		gen->player->move_speed = 0.1;
		gen->enemy->move_speed = gen->player->move_speed;
		gen->flags->terror_mode = !gen->flags->terror_mode;
		start_terror_music(gen);
	}
	if (key == XK_Caps_Lock && !gen->kboard->key_caps_lock)
	{
		gen->kboard->key_caps_lock = true;
		gen->flags->mouse_on = !gen->flags->mouse_on;
	}
	if (key == XK_i && !gen->kboard->key_i)
	{
		gen->kboard->key_i = true;
		gen->flags->info = !gen->flags->info;
	}
	if (key == XK_m && !gen->kboard->key_m)
	{
		gen->kboard->key_m = true;
		gen->flags->minimap = !gen->flags->minimap;
	}
	if (key == XK_e && !gen->kboard->key_m)
	{
		gen->kboard->key_e = true;
		gen->flags->enemy_mini = !gen->flags->enemy_mini;
	}
	if ((key >= XK_1 && key <= XK_5) && !gen->flags->terror_mode)
	{
		index = key - XK_1;
		gen->flags->music_on = !gen->flags->music_on;
		stop_all_sounds(gen);
		play_sound(gen, audio_files[index], 1);
		if (key == XK_1)
			gen->kboard->key_num_one = true;
		if (key == XK_2)
			gen->kboard->key_num_two = true;
		if (key == XK_3)
			gen->kboard->key_num_three = true;
		if (key == XK_4)
			gen->kboard->key_num_four = true;
		if (key == XK_5)
			gen->kboard->key_num_five = true;
	}
	if (key == XK_6 && !gen->flags->terror_mode)
		stop_all_sounds(gen);
	return (0);
}

int	key_release(int key, t_gen *gen)
{
	if (key == XK_w)
	{
		gen->kboard->key_w = false;
	}
	if (key == XK_s)
	{
		gen->kboard->key_s = false;
	}
	if (key == XK_a)
	{
		gen->kboard->key_a = false;
	}
	if (key == XK_d)
	{
		gen->kboard->key_d = false;
	}
	if (key == XK_Left)
	{
		gen->kboard->key_left = false;
	}
	if (key == XK_Right)
	{
		gen->kboard->key_right = false;
	}
	if (key == XK_Control_L)
	{
		if (gen->flags->terror_mode)
		{
			gen->player->move_speed = gen->def_values->terror_player_move_speed;
			gen->enemy->move_speed = gen->player->move_speed - 0.001;
		}
		else
		{
			gen->player->move_speed = 0.05;
			gen->player->rotate_speed = 0.045;
			gen->player->fov -= 0.07;
			gen->kboard->control_left = false;
		}
	}
	if (key == XK_Shift_L)
	{
		gen->player->move_speed = 0.05;
		gen->player->rotate_speed = 0.045;
		gen->kboard->shift_left = false;
	}
	if (key == XK_m)
		gen->kboard->key_m = false;
	if (key == XK_x)
		gen->kboard->key_x = false;
	if (key == XK_z)
		gen->kboard->key_z = false;
	if (key == XK_f)
		gen->kboard->key_f = false;
	if (key == XK_l)
		gen->kboard->key_l = false;
	if (key == XK_t)
	{
		if (!gen->flags->terror_mode) // If we just toggled it off
			stop_all_sounds(gen);
		gen->kboard->key_t = false;
	}
	if (key == XK_Caps_Lock)
		gen->kboard->key_caps_lock = false;
	if (key == XK_i)
		gen->kboard->key_i = false;
	if (key == XK_e)
		gen->kboard->key_e = false;
	return (0);
}

static void	set_player_dir(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else if (c == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
	else if (c == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	search_in_matrix(t_gen *gen, char c)
{
	int	row;
	int	col;

	row = 0;
	while (gen->parse->map[row])
	{
		col = 0;
		while (gen->parse->map[row][col])
		{
			if (gen->parse->map[row][col] == c)
			{
				gen->player->x = col + 0.5;
				gen->player->y = row + 0.5;
				set_player_dir(gen->player, c);
				return ;
			}
			col++;
		}
		row++;
	}
}

int	get_player_position(t_gen *gen)
{
	search_in_matrix(gen, 'N');
	search_in_matrix(gen, 'S');
	search_in_matrix(gen, 'E');
	search_in_matrix(gen, 'W');
	return (0);
}

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

char	*ft_strcat(char *dst, char *srce)
{
	unsigned char	*dest;
	unsigned char	*src;
	int				i;
	int				j;

	dest = (unsigned char *)dst;
	src = (unsigned char *)srce;
	i = ft_strlen(dst);
	j = 0;
	while (src[j])
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return ((char *)dest);
}

int	png_name_to_xpm(t_gen *gen, char *xpm_files[4])
{
	char	*name;
	char	*dot;
	int		len;

	for (int i = 0; i < 4; i++)
	{
		name = gen->parse->textures_info[i];
		if (!name)
			return (0);
		dot = strrchr(name, '.');
		len = dot ? (size_t)(dot - name) : strlen(name);
		xpm_files[i] = malloc(len + ft_strlen(".xpm") + 1);
		if (!xpm_files[i])
			return (0);
		ft_strncpy(xpm_files[i], name, len);
		xpm_files[i][len] = '\0';
		ft_strcat(xpm_files[i], ".xpm");
	}
	return (1);
}

static size_t	ft_putnbr_fake(int n)
{
	size_t	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		count++;
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	digits;
	size_t	i;
	char	*str;
	long	num;

	num = n;
	digits = ft_putnbr_fake(n);
	str = (char *)malloc(digits + 1);
	if (!str)
		return (NULL);
	str[digits] = '\0';
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	i = digits - 1;
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		str[i--] = (num % 10) + '0';
		num /= 10;
	}
	return (str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = (char *)malloc(i + j + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, i);
	ft_memcpy(str + i, s2, j);
	str[i + j] = '\0';
	return (str);
}

int	ft_clamp(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return max;
	return value;
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

t_texture	*load_xpm_texture(void *mlx_ptr, char *file)
{
	t_texture	*tex;

	tex = malloc(sizeof(t_texture));
	if (!tex)
		return NULL;
	tex->img = mlx_xpm_file_to_image(mlx_ptr, file, &tex->width, &tex->height);
	if (!tex->img)
	{
		free(tex);
		return NULL;
	}
	tex->data = (int *)mlx_get_data_addr(tex->img, &(int){0}, &(int){0},
			&(int){0});
	return tex;
}
