#include "./headers/cub3d.h"
#include "headers/mlx.h"

int mouse_looking(t_gen *gen)
{
    int direction_x;
    int cursor_x = WIN_WIDTH / 2;
    int cursor_y = WIN_HEIGHT / 2;

    mlx_mouse_hide(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr);
    mlx_mouse_get_pos(gen->mlx_data->mlx_ptr,gen->mlx_data->win_ptr,&gen->mouse->x,&gen->mouse->y);
    direction_x = gen->mouse->x - cursor_x;
    if (direction_x != 0)
        rotate_player(gen, direction_x * gen->mouse->sens);
    mlx_mouse_move(gen->mlx_data->mlx_ptr,gen->mlx_data->win_ptr,cursor_x,cursor_y);
    return (1);
}

