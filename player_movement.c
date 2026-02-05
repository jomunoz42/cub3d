#include "./headers/cub3d.h"
#include "headers/general.h"
#include "headers/mlx.h"

void rotate_player(t_gen *gen, double angle)
{
	double first_direction_x = gen->player->dir_x;
	double first_plane_x = gen->player->plane_x;

	gen->player->dir_x = gen->player->dir_x * cos(angle)
		- gen->player->dir_y * sin(angle);
	gen->player->dir_y = first_direction_x * sin(angle)
		+ gen->player->dir_y * cos(angle);

	gen->player->plane_x = gen->player->plane_x * cos(angle)
		- gen->player->plane_y * sin(angle);
	gen->player->plane_y = first_plane_x * sin(angle)
		+ gen->player->plane_y * cos(angle);
}

void clear_image(t_img_data *img, int color)
{
    int x, y;
    for (y = 0; y < WIN_HEIGHT; y++)
        for (x = 0; x < WIN_WIDTH; x++)
            copied_mlx_pixel_put(img, x, y, color);
}

void update_player(t_gen *gen)
{
    double nx = gen->player->x;
    double ny = gen->player->y;

    if (gen->kboard->key_w)
    {
        nx += gen->player->dir_x * gen->player->move_speed;
        ny += gen->player->dir_y * gen->player->move_speed;
    }
    if (gen->kboard->key_s)
    {
        nx -= gen->player->dir_x * gen->player->move_speed;
        ny -= gen->player->dir_y * gen->player->move_speed;
    }
    if (gen->kboard->key_a)
    {
        nx -= gen->player->plane_x * gen->player->move_speed;
        ny -= gen->player->plane_y * gen->player->move_speed;
    }
    if (gen->kboard->key_d)
    {
        nx += gen->player->plane_x * gen->player->move_speed;
        ny += gen->player->plane_y * gen->player->move_speed;
    }
    if (gen->kboard->key_right)
        rotate_player(gen, gen->player->rotate_speed);
    if (gen->kboard->key_left)
        rotate_player(gen, -gen->player->rotate_speed);
    if (!collision(gen, gen->player->y, nx + gen->player->dir_x * WALL_MARGIN))
        gen->player->x = nx;
    if (!collision(gen, ny + gen->player->dir_y * WALL_MARGIN, gen->player->x))
        gen->player->y = ny;
    if (!gen->flags->terror_mode && gen->kboard->control_left == false)
        gen->player->move_speed = 0.05;
}

char *ft_dtoa_fixed(double v)
{
    char *a;
    char *b;
    char *tmp;
    int iv = (int)v;
    int frac = (int)((v - iv) * 1000);

    a = ft_itoa(iv);
    b = ft_itoa(frac < 0 ? -frac : frac);
    tmp = ft_strjoin(a, ".");
    free(a);
    a = ft_strjoin(tmp, b);
    free(tmp);
    free(b);
    return a;
}

char * print_helper(char *which_info, double what_to_convert)
{
    char *num = ft_dtoa_fixed(what_to_convert);
    if (!num)
        return NULL;
    char *text = ft_strjoin(which_info, num);
    if (!text)
    {
        free(num);
        return NULL;
    }
    free(num);
    return (text);
}
void print_info(t_gen *gen)
{
    char *dir_x = print_helper("Direction x: ", gen->player->dir_x);
    char *dir_y = print_helper("Direction y: ", gen->player->dir_y);
    char *plane_x = print_helper("Plane x: ", gen->player->plane_x);
    char *plane_y = print_helper("Plane y: ", gen->player->plane_y);
    char *x = print_helper("X: ", gen->player->x);
    char *y = print_helper("Y: ", gen->player->y);
    char *fov = print_helper("FOV: ", gen->player->fov);
    char *mouse_x = print_helper("Mouse x: ", (double)gen->mouse->x);
    char *mouse_y = print_helper("Mouse y: ", (double)gen->mouse->y);
    char *zoom_lvl = print_helper("Minimap zoom level: ", gen->minimap->zoom_level);
    char *player_speed = print_helper("Player speed: ", gen->player->move_speed);

    int i;
    const double spacing = 11;
    if (gen->flags->minimap)
        i = 220;
    else
        i = 10;
    mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, i += spacing,
            INFO_TEXT_COLOR, dir_x);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, i += spacing,
            INFO_TEXT_COLOR, dir_y);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, i += spacing,
            INFO_TEXT_COLOR, plane_x);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, i += spacing,
            INFO_TEXT_COLOR, plane_y);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, i += spacing,
            INFO_TEXT_COLOR, x);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, i += spacing,
            INFO_TEXT_COLOR, y);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, i += spacing,
            INFO_TEXT_COLOR, fov);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, i += spacing,
            INFO_TEXT_COLOR, mouse_x);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, i += spacing,
            INFO_TEXT_COLOR, mouse_y);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, i += spacing,
            INFO_TEXT_COLOR, zoom_lvl);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, i += spacing,
            INFO_TEXT_COLOR, player_speed);
    free(dir_x);
    free(dir_y);
    free(plane_x);
    free(plane_y);
    free(x);
    free(y);
    free(fov);
    free(mouse_x);
    free (mouse_y);
    free(zoom_lvl);
    free(player_speed);
}

void apply_vignette_to_image(t_gen *gen, t_img_data *img)
{
    if (gen->flags->terror_mode) 
    {
        for (int y = 0; y < img->height; y++)
        {
            for (int x = 0; x < img->width; x++)
            {
                int color = get_pixel_color_img(img, x, y);
                float f = img->vignette[y * img->width + x];

                int r = ((color >> 16) & 0xFF) * f;
                int g = ((color >> 8) & 0xFF) * f;
                int b = (color & 0xFF) * f;

                copied_mlx_pixel_put(img, x, y, (r << 16) | (g << 8) | b);
            }
        }
    }
}


int game_loop(t_gen *gen)
{
    update_player(gen);              
    clear_image(gen->img_data, 0x000000);
    render_scene(gen);
    mouse_looking(gen);
    if (!gen->flags->terror_mode && gen->flags->minimap)
        draw_minimap(gen);                
    draw_arm(gen);   
    apply_vignette_to_image(gen, gen->img_data);
    mlx_put_image_to_window(
        gen->mlx_data->mlx_ptr,
        gen->mlx_data->win_ptr,
        gen->img_data->img,
        0, 0
    );
    if (gen->flags->info && !gen->flags->terror_mode)
        print_info(gen);
    return 0;
}
