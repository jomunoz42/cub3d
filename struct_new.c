#include "./headers/cub3d.h"

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
						.elements = {0, 0, 0, 0, 0, 0}
	};
	return (new);
}

int main_init(t_gen *gen, char *argv)
{
	(void)argv;
	if (init_all(gen))
		return (0);
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
	return (1);
}

int general_texture_init(t_gen *gen)
{
    for (int i = 0; i < 4; i++)
    {
        gen->texture[i] = malloc(sizeof(t_texture));
        if (!gen->texture[i])
            return 0;
        gen->texture[i]->data = NULL;
        gen->texture[i]->height = 0;
        gen->texture[i]->width = 0;
        gen->texture[i]->img = NULL;
    }
    return 1;
}

void wall_textures_init(t_gen *gen)
{
    int bpp, sl, endian;
    char *xpm_files[4];
    if (!png_name_to_xpm(gen, xpm_files))
    {
        fprintf(stderr, "Failed to convert PNG names to XPM\n");
        exit(1);
    }
    for (int i = 0; i < 4; i++)
    {
		// printf("XPM[%d]: %s\n", i, xpm_files[i]);
        gen->texture[i]->img = mlx_xpm_file_to_image(
            gen->mlx_data->mlx_ptr,
            xpm_files[i],
            &gen->texture[i]->width,
            &gen->texture[i]->height
        );
        if (!gen->texture[i]->img)
        {
            fprintf(stderr, "Failed to load texture %d: %s\n", i, xpm_files[i]);
            exit(1);
        }
        gen->texture[i]->data = (int *)mlx_get_data_addr(
            gen->texture[i]->img, &bpp, &sl, &endian
        );
    }
    for (int i = 0; i < 4; i++)
        free(xpm_files[i]);
}


int	texture_data_init(t_gen *gen)
{
	gen->texture_data = malloc(sizeof(t_texture_data));
	if (!gen->texture_data)
		return (0);
	gen->texture_data->arm_width = 0;
	gen->texture_data->arm_height = 0;
	gen->texture_data->clng_color = color_switch(gen->parse->textures_info[5]);
	gen->texture_data->flr_color = color_switch(gen->parse->textures_info[4]);
	gen->texture_data->horizon = gen->mlx_data->win_height / 2;
	if (!png_size_fd(USER_HAND_PNG, &gen->texture_data->arm_width,
			&gen->texture_data->arm_height))
		return (0);
	// printf("[arm image data] Width: %u, Height: %u\n",
	// 	gen->texture_data->arm_width, gen->texture_data->arm_height);
	return (1);
}

int minimap_init(t_gen *gen)
{
    gen->minimap = malloc(sizeof(t_minimap));
    if (!gen->minimap)
        return 0;

    gen->minimap->map = NULL;
    gen->minimap->width  = gen->mlx_data->win_width * 0.20;
    gen->minimap->height = gen->mlx_data->win_height * 0.20;

    gen->minimap->image.img = mlx_new_image(
        gen->mlx_data->mlx_ptr,
        gen->minimap->width,
        gen->minimap->height
    );
    gen->minimap->image.addr = mlx_get_data_addr(
        gen->minimap->image.img,
        &gen->minimap->image.bits_pixel,
        &gen->minimap->image.line_len,
        &gen->minimap->image.endian
    );
	gen->minimap->image.height = gen->mlx_data->win_height;
	gen->minimap->image.width = gen->mlx_data->win_width;

    return 1;
}


int keyboard_init(t_gen *gen)
{
	gen->kboard = malloc(sizeof(t_keyboard));
	if (!gen->kboard)
		return (0);
	gen->kboard->key_w = false;
	gen->kboard->key_a = false;
	gen->kboard->key_s = false;
	gen->kboard->key_d = false;
	gen->kboard->key_right = false;
	gen->kboard->key_left = false;
	gen->kboard->control_left = false;
	gen->kboard->shift_left = false;
	gen->kboard->key_f = false;
	gen->kboard->key_l = false;
	return (1);
}

int rayhit_init(t_gen *gen)
{
	gen->rayhit = malloc(sizeof(t_rayhit));
	if (!gen->rayhit)
		return (0);
	gen->rayhit->dist = 0;
	gen->rayhit->mapX = 0;
	gen->rayhit->mapY = 0;
	gen->rayhit->side = -1;
	return (1);
}

int player_init(t_gen *gen)
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
	gen->player->rotate_speed = 0.045;
	gen->player->fov = 2.0;
	return (1);
}

int arm_init(t_gen *gen)
{
	gen->arm = malloc(sizeof(t_img_data));
	if (!gen->arm)
		return (0);
	int img_width = (int)gen->texture_data->arm_width;
	int img_height = (int)gen->texture_data->arm_height;
	gen->arm->bits_pixel = 0;
	gen->arm->line_len = 0;
	gen->arm->endian = 0;
	gen->arm->width = 0;
	gen->arm->height = 0;
	gen->arm->img = mlx_xpm_file_to_image(
    gen->mlx_data->mlx_ptr,
    USER_HAND_XPM,
    &img_width,
    &img_height
	);
	gen->arm->addr = mlx_get_data_addr(
		gen->arm->img,
		&gen->arm->bits_pixel,
		&gen->arm->line_len,
		&gen->arm->endian
	);
	return (1);

}

int basic_mlx_init(t_gen *gen)
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
	general_texture_init(gen);
	wall_textures_init(gen);
	// printf("== horizontal line is on %d\n", gen->texture_data->horizon);
	return (0);
}
