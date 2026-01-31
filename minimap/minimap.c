#include "../headers/cub3d.h"

void draw_minimap_tile_pixel(t_gen *gen, int x, int y, int color)
{
    for (int dy = 0; dy < MINIMAP_SCALE; dy++)
        for (int dx = 0; dx < MINIMAP_SCALE; dx++)
            copied_mlx_pixel_put(
                gen->img_data,
                x + dx,
                y + dy,
                color
            );
}

void draw_player_dot(t_gen *gen, int center_x, int center_y)
{
    int size = MINIMAP_SCALE / 3; // player size on minimap
    int half = size / 2;

    for (int y = -half; y <= half; y++)
    {
        for (int x = -half; x <= half; x++)
        {
            copied_mlx_pixel_put(
                gen->img_data,
                center_x + x,
                center_y + y,
                0xFFA500
            );
        }
    }
}

void draw_player_square(t_gen *gen)
{
    int cx = MINIMAP_OFFSET_X + MINIMAP_RADIUS * MINIMAP_SCALE;
    int cy = MINIMAP_OFFSET_Y + MINIMAP_RADIUS * MINIMAP_SCALE;

    int size = MINIMAP_SCALE;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++)
            copied_mlx_pixel_put(
                gen->img_data,
                cx + x,
                cy + y,
                0x0000FF
            );
}

// Called each frame
void draw_minimap(t_gen *gen)
{
    int player_x = (int)gen->player->x;
    int player_y = (int)gen->player->y;

    int start_x = player_x - MINIMAP_RADIUS;
    int start_y = player_y - MINIMAP_RADIUS;

    // Clamp to map bounds
    if (start_x < 0) start_x = 0;
    if (start_y < 0) start_y = 0;
    if (start_x + MINIMAP_TILES > gen->parse->width)
        start_x = gen->parse->width - MINIMAP_TILES;
    if (start_y + MINIMAP_TILES > gen->parse->height)
        start_y = gen->parse->height - MINIMAP_TILES;

    for (int y = 0; y < MINIMAP_TILES; y++)
    {
        for (int x = 0; x < MINIMAP_TILES; x++)
        {
            int map_x = start_x + x;
            int map_y = start_y + y;

            if (map_x < 0 || map_y < 0 || map_y >= gen->parse->height)
                continue;

            int row_len = ft_strlen(gen->parse->map[map_y]);
            if (map_x >= row_len)
                continue;

            int color;
            char tile = gen->parse->map[map_y][map_x];
            if (tile == '1')
                color = 0xFFFFFF;
            else if (tile == '0')
                color = 0x161616;
            else
                continue;

            draw_minimap_tile_pixel(
                gen,
                MINIMAP_OFFSET_X + x * MINIMAP_SCALE,
                MINIMAP_OFFSET_Y + y * MINIMAP_SCALE,
                color
            );
        }
    }

    draw_player_square(gen);
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