#include "./headers/cub3d.h"
#include "headers/general.h"

t_parsing	*parsing_init(void)
{
	t_parsing	*new;

	new = malloc(sizeof(t_parsing));
	if (!new)
		return (NULL);
	*new = (t_parsing){// check and study this later
						.textures_info = NULL,
						.player = '\0',
						.map = NULL,
						.width = 0,
						.height = 0,
						.fd = 0,
						.elements = {0, 0, 0, 0, 0, 0}};
	return (new);
}

void	copy_matrix(char **original_matrix, char ***matrix_to_copy_ptr)
{
	int	matrix_count;

	matrix_count = 0;
	while (original_matrix[matrix_count])
		matrix_count++;
	*matrix_to_copy_ptr = malloc(sizeof(char *) * (matrix_count + 1));
	if (!*matrix_to_copy_ptr)
		return ;
	for (int i = 0; i < matrix_count; i++)
	{
		(*matrix_to_copy_ptr)[i] = ft_strdup(original_matrix[i]);
		if (!(*matrix_to_copy_ptr)[i])
			return ;
	}
	(*matrix_to_copy_ptr)[matrix_count] = NULL;
}

int	main_init(t_gen *gen, char *argv, char **environ)
{
	(void)argv;
	if (init_all(gen))
		return (0);
	copy_matrix(environ, &gen->def_values->env);
	return (1);
}

int	mouse_init(t_gen *gen)
{
	gen->mouse = malloc(sizeof(t_mouse));
	if (!gen->mouse)
		return (0);
	gen->mouse->x = 0;
	gen->mouse->y = 0;
	gen->mouse->previous_x = 0;
	gen->mouse->sens = MOUSE_SENS;
	return (1);
}

int	avg_img_init(t_gen *gen)
{
	gen->img_data = malloc(sizeof(t_img_data));
	if (!gen->img_data)
		return (0);
	gen->img_data->addr = NULL;
	gen->img_data->img = NULL;
	gen->img_data->endian = 0;
	gen->img_data->line_len = 0;
	gen->img_data->bits_pixel = 0;
	gen->img_data->vignette = 0;
	return (1);
}

void	init_vignette(t_img_data *img)
{
	double	cx;
	double	cy;
	double	max_dist;
	double	dx;
	double	dy;
	double	dist;
	double	t;
			double factor;

	cx = img->width / 2.0;
	cy = img->height / 2.0;
	max_dist = sqrt(cx * cx + cy * cy);
	double inner_radius = 0.35; // 👈 tweak this (0.25–0.45)
	double max_light = 0.6;     // 👈 how dark the center is
	img->vignette = malloc(sizeof(float) * img->width * img->height);
	if (!img->vignette)
		return ;
	for (int y = 0; y < img->height; y++)
	{
		for (int x = 0; x < img->width; x++)
		{
			dx = x - cx;
			dy = y - cy;
			dist = sqrt(dx * dx + dy * dy);
			t = dist / max_dist;
			if (t < inner_radius)
				factor = 1.0;
			else
			{
				factor = 1.0 - (t - inner_radius) / (1.0 - inner_radius);
				factor = pow(factor, 2.0); // darkness curve
			}
			factor *= max_light; // overall darkness
			if (factor < 0.0)
				factor = 0.0;
			img->vignette[y * img->width + x] = factor;
		}
	}
}

int	general_texture_init(t_gen *gen)
{
	for (int i = 0; i < 4; i++)
	{
		gen->texture[i] = malloc(sizeof(t_texture));
		if (!gen->texture[i])
			return (0);
		gen->texture[i]->data = NULL;
		gen->texture[i]->height = 0;
		gen->texture[i]->width = 0;
		gen->texture[i]->img = NULL;
	}
	for (int i = 0; i < 4; i++)
	{
		gen->terror_texture[i] = malloc(sizeof(t_texture));
		if (!gen->terror_texture[i])
			return (0);
		gen->terror_texture[i]->data = NULL;
		gen->terror_texture[i]->height = 0;
		gen->terror_texture[i]->width = 0;
		gen->terror_texture[i]->img = NULL;
	}
	for (int i = 0; i < 4; i++)
	{
		gen->ghost_enemy[i] = malloc(sizeof(t_texture));
		if (!gen->ghost_enemy[i])
			return (0);
		gen->ghost_enemy[i]->data = NULL;
		gen->ghost_enemy[i]->height = 0;
		gen->ghost_enemy[i]->width = 0;
		gen->ghost_enemy[i]->img = NULL;
	}
	for (int i = 0; i < 2; i++)
	{
		gen->cthulhu_enemy[i] = malloc(sizeof(t_texture));
		if (!gen->cthulhu_enemy[i])
			return (0);
		gen->cthulhu_enemy[i]->data = NULL;
		gen->cthulhu_enemy[i]->height = 0;
		gen->cthulhu_enemy[i]->width = 0;
		gen->cthulhu_enemy[i]->img = NULL;
	}
	for (int i = 0; i < 8; i++)
	{
		gen->skeleton_enemy[i] = malloc(sizeof(t_texture));
		if (!gen->skeleton_enemy[i])
			return (0);
		gen->skeleton_enemy[i]->data = NULL;
		gen->skeleton_enemy[i]->height = 0;
		gen->skeleton_enemy[i]->width = 0;
		gen->skeleton_enemy[i]->img = NULL;
	}
	return (1);
}

static void	load_textures(t_gen *gen, t_texture **dst, char **xpm_files, int count)
{
	int bpp, sl, endian;
	for (int i = 0; i < count; i++)
	{
		dst[i]->img = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr,
				xpm_files[i], &dst[i]->width, &dst[i]->height);
		if (!dst[i]->img)
		{
			printf("Failed to load texture %d: %s\n", i, xpm_files[i]);
			exit(1);
		}
		dst[i]->data = (int *)mlx_get_data_addr(dst[i]->img, &bpp, &sl,
				&endian);
	}
}

void	wall_textures_init(t_gen *gen)
{
	char	*normal_xpm[4];
	char	*terror_xpm[4];
	char	*ghost_xpm[4];
	char	*cthulhu_xpm[4];
	char	*skeleton_xpm[8];

	if (!png_name_to_xpm(gen, normal_xpm))
	{
		ft_putstr_fd("Failed to convert normal PNG names\n", 2);
		exit(1);
	}
	terror_xpm[0] = ft_strdup("imgs/scary4.xpm");
	terror_xpm[1] = ft_strdup("imgs/scary1.xpm");
	terror_xpm[2] = ft_strdup("imgs/scary2.xpm");
	terror_xpm[3] = ft_strdup("imgs/scary3.xpm");
	ghost_xpm[0] = ft_strdup("imgs/ghost_1.xpm");
	ghost_xpm[1] = ft_strdup("imgs/ghost_2.xpm");
	ghost_xpm[2] = ft_strdup("imgs/ghost_3.xpm");
	ghost_xpm[3] = ft_strdup("imgs/ghost_4.xpm");
	cthulhu_xpm[0] = ft_strdup("imgs/cthulhu_1.xpm");
	cthulhu_xpm[1] = ft_strdup("imgs/cthulhu_2.xpm");
	skeleton_xpm[0] = ft_strdup("imgs/skel_1.xpm");
	skeleton_xpm[1] = ft_strdup("imgs/skel_2.xpm");
	skeleton_xpm[2] = ft_strdup("imgs/skel_3.xpm");
	skeleton_xpm[3] = ft_strdup("imgs/skel_4.xpm");
	skeleton_xpm[4] = ft_strdup("imgs/skel_5.xpm");
	skeleton_xpm[5] = ft_strdup("imgs/skel_6.xpm");
	skeleton_xpm[6] = ft_strdup("imgs/skel_7.xpm");
	skeleton_xpm[7] = ft_strdup("imgs/skel_8.xpm");
	load_textures(gen, gen->texture, normal_xpm, 4);
	load_textures(gen, gen->terror_texture, terror_xpm, 4);
	load_textures(gen, gen->ghost_enemy, ghost_xpm, 4);
	load_textures(gen, gen->cthulhu_enemy, cthulhu_xpm, 2);
	load_textures(gen, gen->skeleton_enemy, skeleton_xpm, 8);
	gen->door_texture = load_xpm_texture(gen->mlx_data->mlx_ptr, "imgs/porta_normal.xpm");
	gen->door_texture2 = load_xpm_texture(gen->mlx_data->mlx_ptr, "imgs/terror_door.xpm");
	for (int i = 0; i < 8; i++)
	{
		if (i < 2)
			free(cthulhu_xpm[i]);
		if (i < 4)
		{
			free(normal_xpm[i]);
			free(terror_xpm[i]);
			free(ghost_xpm[i]);
		}
		free(skeleton_xpm[i]);
	}
}

int	texture_data_init(t_gen *gen)
{
	gen->texture_data = malloc(sizeof(t_texture_data));
	if (!gen->texture_data)
		return (0);
	gen->texture_data->arm_width = 0;
	gen->texture_data->arm_height = 0;
	gen->texture_data->terror_arm_width = 0;
	gen->texture_data->terror_arm_height = 0;
	gen->texture_data->clng_color = color_switch(gen->parse->textures_info[5]);
	gen->texture_data->flr_color = color_switch(gen->parse->textures_info[4]);
	gen->texture_data->horizon = gen->mlx_data->win_height / 2;
	if (!png_size_fd(USER_HAND_PNG, &gen->texture_data->arm_width,
			&gen->texture_data->arm_height))
		return (0);
	if (!png_size_fd(USER_TERROR_HAND_PNG, &gen->texture_data->terror_arm_width,
			&gen->texture_data->terror_arm_height))
		return (0);
	return (1);
}

int	minimap_init(t_gen *gen)
{
	gen->minimap = malloc(sizeof(t_minimap));
	if (!gen->minimap)
		return (0);
	gen->minimap->map = NULL;
	gen->minimap->width = gen->mlx_data->win_width * 0.20;
	gen->minimap->height = gen->mlx_data->win_height * 0.20;
	gen->minimap->image.img = mlx_new_image(gen->mlx_data->mlx_ptr,
			gen->minimap->width, gen->minimap->height);
	gen->minimap->image.addr = mlx_get_data_addr(gen->minimap->image.img,
			&gen->minimap->image.bits_pixel, &gen->minimap->image.line_len,
			&gen->minimap->image.endian);
	gen->minimap->image.height = gen->mlx_data->win_height;
	gen->minimap->image.width = gen->mlx_data->win_width;
	gen->minimap->zoom_level = 14.0;
	return (1);
}

int	keyboard_init(t_gen *gen)
{
	gen->kboard = malloc(sizeof(t_keyboard));
	if (!gen->kboard)
		return (0);
	gen->kboard->key_w = false;
	gen->kboard->key_a = false;
	gen->kboard->key_s = false;
	gen->kboard->key_d = false;
	gen->kboard->key_e = false;
	gen->kboard->tab = false;
	gen->kboard->key_right = false;
	gen->kboard->key_left = false;
	gen->kboard->control_left = false;
	gen->kboard->shift_left = false;
	gen->kboard->key_f = false;
	gen->kboard->key_l = false;
	gen->kboard->key_t = false;
	gen->kboard->key_i = false;
	gen->kboard->key_z = false;
	gen->kboard->key_x = false;
	gen->kboard->key_m = false;
	gen->kboard->key_e = false;
	gen->kboard->key_caps_lock = false;
	gen->kboard->key_num_one = false;
	gen->kboard->key_num_two = false;
	gen->kboard->key_num_three = false;
	gen->kboard->key_num_four = false;
	gen->kboard->key_num_five = false;
	gen->kboard->key_num_six = false;
	return (1);
}

int	rayhit_init(t_gen *gen)
{
	gen->rayhit = malloc(sizeof(t_rayhit));
	if (!gen->rayhit)
		return (0);
	gen->rayhit->dist = 0;
	gen->rayhit->map_x = 0;
	gen->rayhit->map_y = 0;
	gen->rayhit->side = -1;
	ft_memset(gen->rayhit->zbuffer, 0, sizeof(gen->rayhit->zbuffer));
	return (1);
}

int	player_init(t_gen *gen)
{
	gen->player = malloc(sizeof(t_player));
	if (!gen->player)
		return (0);
	gen->player->x = 1;
	gen->player->y = 1;
	gen->player->dir_x = 0;
	gen->player->dir_y = 0;
	gen->player->plane_x = 0;
	gen->player->plane_y = 0;
	gen->player->move_speed = 0.05;
	gen->player->rotate_speed = DEFAULT_PLAYER_ROTATE_SPEED;
	gen->player->fov = DEFAULT_PLAYER_FOV;
	return (1);
}

int	arm_init(t_gen *gen)
{
	int	img_width;
	int	img_height;

	gen->arm = malloc(sizeof(t_img_data));
	if (!gen->arm)
		return (0);
	img_width = (int)gen->texture_data->arm_width;
	img_height = (int)gen->texture_data->arm_height;
	gen->arm->bits_pixel = 0;
	gen->arm->line_len = 0;
	gen->arm->endian = 0;
	gen->arm->width = 0;
	gen->arm->height = 0;
	gen->arm->img = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr, USER_HAND_XPM,
			&img_width, &img_height);
	gen->arm->addr = mlx_get_data_addr(gen->arm->img, &gen->arm->bits_pixel,
			&gen->arm->line_len, &gen->arm->endian);
	return (1);
}

int	terror_arm_init(t_gen *gen)
{
	int	img_width;
	int	img_height;

	gen->terror_arm = malloc(sizeof(t_img_data));
	if (!gen->terror_arm)
		return (0);
	img_width = (int)gen->texture_data->terror_arm_width;
	img_height = (int)gen->texture_data->terror_arm_height;
	gen->terror_arm->bits_pixel = 0;
	gen->terror_arm->line_len = 0;
	gen->terror_arm->endian = 0;
	gen->terror_arm->width = 0;
	gen->terror_arm->height = 0;
	gen->terror_arm->img = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr,
			USER_TERROR_HAND_XPM, &img_width, &img_height);
	gen->terror_arm->addr = mlx_get_data_addr(gen->terror_arm->img,
			&gen->terror_arm->bits_pixel, &gen->terror_arm->line_len,
			&gen->terror_arm->endian);
	return (1);
}

int	basic_mlx_init(t_gen *gen)
{
	gen->mlx_data->mlx_ptr = mlx_init();
	if (!gen->mlx_data->mlx_ptr)
		return (0);
	gen->mlx_data->win_ptr = NULL;
	gen->arm = NULL;
	gen->mlx_data->win_width = WIN_WIDTH;
	gen->mlx_data->win_height = WIN_HEIGHT;
	return (1);
}

int	init_flags(t_gen *gen)
{
	gen->flags = malloc(sizeof(t_flags));
	if (!gen->flags)
		return (0);
	gen->flags->info = true;
	gen->flags->terror_mode = false;
	gen->flags->minimap = true;
	gen->flags->mouse_on = true;
	gen->flags->enemy_mini = true;
	gen->flags->music_on = false;
	return (1);
}

int	def_values_init(t_gen *gen)
{
	gen->def_values = malloc(sizeof(t_def_values));
	if (!gen->def_values)
		return (0);
	gen->def_values->fov = gen->player->fov;
	gen->def_values->player_rotation_speed = gen->player->rotate_speed;
	gen->def_values->player_move_speed = gen->player->move_speed;
	gen->def_values->player_x = gen->player->x;
	gen->def_values->player_y = gen->player->y;
	gen->def_values->minimap_zoom_level = gen->minimap->zoom_level;
	gen->def_values->terror_player_move_speed = gen->def_values->player_move_speed
		+ 0.05;
	gen->def_values->env = NULL;
	gen->def_values->sounds.pids = malloc(sizeof(pid_t) * 128);
	gen->def_values->sounds.terror_music_pid = 0;
	gen->def_values->sounds.count = 0;
	gen->def_values->sounds.capacity = 128;
	return (1);
}

int	enemy_init(t_gen *gen)
{
	int i;

	i = 0;
	gen->enemy_count = count_enemies_in_map(gen);
	if (gen->enemy_count == 0)
        return (1);
	printf("Enemies in map: %d\n", gen->enemy_count);

	gen->enemy = malloc(sizeof(t_enemy) * gen->enemy_count);
	if (!gen->enemy)
		return (0);

	while (i < gen->enemy_count)
	{
		gen->enemy[i].move_speed = gen->def_values->player_move_speed;
		gen->enemy[i].size = 20;
		gen->enemy[i].x = 0;
		gen->enemy[i].y = 0;
		gen->enemy[i].enemy_frame = 0;
		gen->enemy[i].enemy_timer = 0;
		gen->enemy->type = ENEMY_SKELETON;
		find_enemy_from_map(gen, i);
		printf("Enemy position is x[%d][%d]\n", (int)gen->enemy[i].x,
		(int)gen->enemy[i].y);
		i++;
	}
	return (1);
}

int enemy_texture_init(t_gen *gen)
{
    gen->enemy_tex = load_xpm_texture(
        gen->mlx_data->mlx_ptr, ENEMY_SPRITE_XPM);

    if (!gen->enemy_tex)
    {
        ft_putstr_fd("Error\nError: failed to load enemy texture\n", 2);
        exit(1);
    }
    return (1);
}


int	init_all(t_gen *gen)
{
	gen->mlx_data = malloc(sizeof(t_mlx_data));
	if (!gen->mlx_data)
		return (1);
	basic_mlx_init(gen);
	texture_data_init(gen);
	avg_img_init(gen);
	player_init(gen);
	minimap_init(gen);
	keyboard_init(gen);
	rayhit_init(gen);
	arm_init(gen);
	terror_arm_init(gen);
	general_texture_init(gen);
	wall_textures_init(gen);
	mouse_init(gen);
	init_flags(gen);
	def_values_init(gen);
	enemy_init(gen);
	enemy_texture_init(gen);
	return (0);
}
