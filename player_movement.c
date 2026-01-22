#include "./headers/cub3d.h"
#include "headers/general.h"


int move_player(int keysym, t_gen *gen)
{
    if (keysym == XK_w || keysym == XK_Up)
        gen->player->y -= 1;
    else if (keysym == XK_a || keysym == XK_Left)
        gen->player->x -= 1;
    else if (keysym == XK_s || keysym == XK_Down)
        gen->player->y += 1;
    else if (keysym == XK_d || keysym == XK_Right)
        gen->player->x += 1;

    draw_minimap(gen);
    return (0);
}


