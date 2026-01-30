#include "../headers/cub3d.h"

// Called once at initialization
void draw_static_minimap(t_gen *gen)
{
    for (int row = 0; gen->parse->map[row]; row++)
    {
        for (int col = 0; gen->parse->map[row][col]; col++)
        {
            int color;
            if (gen->parse->map[row][col] == '1')
                color = 0xFFFFFF;
            else if (gen->parse->map[row][col] == '0')
                color = 0x161616;
            else
                continue;

            for (int dy = 0; dy < MINIMAP_SCALE; dy++)
                for (int dx = 0; dx < MINIMAP_SCALE; dx++)
                    copied_mlx_pixel_put(
                        &gen->minimap->image,
                        col * MINIMAP_SCALE + dx,
                        row * MINIMAP_SCALE + dy,
                        color
                    );
        }
    }
}

// Called each frame
void draw_minimap(t_gen *gen)
{
    // Copy static map into main screen
    for (int y = 0; y < gen->minimap->height; y++)
        for (int x = 0; x < gen->minimap->width; x++)
            copied_mlx_pixel_put(
                gen->img_data,
                x,
                y,
                get_pixel_color_img(&gen->minimap->image, x, y)
            );

    // Draw player
    int px = (int)(gen->player->x * MINIMAP_SCALE);
    int py = (int)(gen->player->y * MINIMAP_SCALE);
    draw_minimap_tile(gen, py / MINIMAP_SCALE, px / MINIMAP_SCALE, 0xFFA500);

    // Draw FOV
    draw_minimap_fov(gen);
}

void draw_minimap_tile(t_gen *gen, int row, int col, int color)
{
    for (int dy = 0; dy < MINIMAP_SCALE; dy++)
        for (int dx = 0; dx < MINIMAP_SCALE; dx++)
            copied_mlx_pixel_put(
                gen->img_data,
                col * MINIMAP_SCALE + dx,
                row * MINIMAP_SCALE + dy,
                color
            );
}


void redraw_map_tiles(t_gen *gen, int y, int x, int prev[2])
{
    (void)prev;
    (void)x;
    (void)y;

    draw_minimap_tile(gen,prev[0],prev[1],0x161616);
    draw_minimap_tile( gen, y, x, 0xFFA500);
    // draw_minimap(gen);        // redesenha mapa + player

    mlx_put_image_to_window(gen->mlx_data->mlx_ptr,gen->mlx_data->win_ptr,
        gen->minimap->image.img,0, 0);
}