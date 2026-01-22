#include "./headers/cub3d.h"
#include "headers/general.h"

void draw_minimap_tile(t_gen *gen, int row, int col, int color)
{
    int dx;
    int dy;

    dy = 0;
    while (dy < MINIMAP_SCALE)
    {
        dx = 0;
        while (dx < MINIMAP_SCALE)
        {
            copied_mlx_pixel_put(
                &gen->minimap->image,
                col * MINIMAP_SCALE + dx,
                row * MINIMAP_SCALE + dy,
                color
            );
            dx++;
        }
        dy++;
    }
}

bool collision(t_gen *gen, int next_y, int next_x)
{
    return (gen->parse->map[next_y][next_x] == '1');
}


void redraw_map_tiles(t_gen *gen, int y, int x, int prev[2])
{
    draw_minimap_tile(
        gen,
        prev[0],     
        prev[1],     
        0x161616   
    );

    draw_minimap_tile( gen, y, x, 0xFFA500);

    mlx_put_image_to_window(
        gen->mlx_data->mlx_ptr,
        gen->mlx_data->win_ptr,
        gen->minimap->image.img,
        0,
        0
    );
}

int move_player(int keysym, t_gen *gen)
{
    int prev[2] = {(int)gen->player->y, (int)gen->player->x};
    int next_x = prev[1];
    int next_y = prev[0];

    if (keysym == XK_w || keysym == XK_Up)
        next_y--;
    else if (keysym == XK_s || keysym == XK_Down)
        next_y++;
    else if (keysym == XK_a || keysym == XK_Left)
        next_x--;
    else if (keysym == XK_d || keysym == XK_Right)
        next_x++;

    if (!collision(gen, next_y, next_x))
    {
        gen->player->x = next_x;
        gen->player->y = next_y;
        redraw_map_tiles(gen, next_y, next_x, prev);
    }

    return (0);
}



