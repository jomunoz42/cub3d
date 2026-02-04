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

    mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, 230,
            0xFFFFFF, dir_x);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, 240,
            0xFFFFFF, dir_y);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, 250,
            0xFFFFFF, plane_x);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, 260,
            0xFFFFFF, plane_y);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, 270,
            0xFFFFFF, x);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, 280,
            0xFFFFFF, y);
        mlx_string_put(
        gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,10, 290,
            0xFFFFFF, fov);

}


int game_loop(t_gen *gen)
{
    update_player(gen);              
    clear_image(gen->img_data, 0x000000); // Limpa a tela
    render_scene(gen);                
    draw_minimap(gen);                
    draw_arm(gen);      
    mlx_put_image_to_window(
        gen->mlx_data->mlx_ptr,
        gen->mlx_data->win_ptr,
        gen->img_data->img,
        0, 0
    );
    print_info(gen);
    return 0;
}

