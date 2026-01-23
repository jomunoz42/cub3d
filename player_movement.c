#include "./headers/cub3d.h"
#include "headers/general.h"

int move_player(int keysym, t_gen *gen)
{
    int prev[2] = {(int)gen->player->y, (int)gen->player->x};
    int next_x = prev[1];
    int next_y = prev[0];

    if (keysym == XK_w)
        next_y--;
    else if (keysym == XK_s)
        next_y++;
    else if (keysym == XK_a)
        next_x--;
    else if (keysym == XK_d)
        next_x++;

    if (!collision(gen, next_y, next_x))
    {
        gen->player->x = next_x;
        gen->player->y = next_y;
        redraw_map_tiles(gen, next_y, next_x, prev);
    }

    return (0);
}

int key_handler(int keysym, t_gen *gen)
{
    if (keysym == XK_Escape)
        handle_exit(keysym);

    else if (keysym == XK_w || keysym == XK_a
          || keysym == XK_s || keysym == XK_d)
        move_player(keysym, gen);
    return (0);
}



