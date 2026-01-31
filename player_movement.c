#include "./headers/cub3d.h"
#include "headers/general.h"

void rotate_player(t_gen *gen, double angle)
{
	double oldDirX = gen->player->dir_x;
	double oldPlaneX = gen->player->plane_x;

	gen->player->dir_x = gen->player->dir_x * cos(angle)
		- gen->player->dir_y * sin(angle);
	gen->player->dir_y = oldDirX * sin(angle)
		+ gen->player->dir_y * cos(angle);

	gen->player->plane_x = gen->player->plane_x * cos(angle)
		- gen->player->plane_y * sin(angle);
	gen->player->plane_y = oldPlaneX * sin(angle)
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
        nx += gen->player->dir_x * MOVE_SPEED;
        ny += gen->player->dir_y * MOVE_SPEED;
    }
    if (gen->kboard->key_s)
    {
        nx -= gen->player->dir_x * MOVE_SPEED;
        ny -= gen->player->dir_y * MOVE_SPEED;
    }
    if (gen->kboard->key_a)
    {
        nx -= gen->player->plane_x * MOVE_SPEED;
        ny -= gen->player->plane_y * MOVE_SPEED;
    }
    if (gen->kboard->key_d)
    {
        nx += gen->player->plane_x * MOVE_SPEED;
        ny += gen->player->plane_y * MOVE_SPEED;
    }
    if (gen->kboard->key_right)
        rotate_player(gen, ROTATION_SPEED);
    if (gen->kboard->key_left)
        rotate_player(gen, -ROTATION_SPEED);


    if (!collision(gen, gen->player->y, nx + gen->player->dir_x * WALL_MARGIN))
        gen->player->x = nx;
    if (!collision(gen, ny + gen->player->dir_y * WALL_MARGIN, gen->player->x))
        gen->player->y = ny;
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
    return 0;
}

