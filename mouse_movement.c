#include "./headers/cub3d.h"
#include "headers/mlx.h"

int mouse_looking(t_gen *gen)
{
    int dx;

    mlx_mouse_hide(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr);
    mlx_mouse_get_pos(
        gen->mlx_data->mlx_ptr,
        gen->mlx_data->win_ptr,
        &gen->mouse->x,
        &gen->mouse->y
    );

    dx = gen->mouse->x - gen->mouse->previous_x;

    if (dx != 0)
        rotate_player(gen, dx * gen->mouse->sens);

    gen->mouse->previous_x = gen->mouse->x;
    return (1);
}
