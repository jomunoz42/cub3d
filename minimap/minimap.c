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


// Called each frame
void draw_minimap(t_gen *gen)
{
    int player_x = (int)gen->player->x;
    int player_y = (int)gen->player->y;

    for (int dy = -MINIMAP_RADIUS; dy <= MINIMAP_RADIUS; dy++)
    {
        for (int dx = -MINIMAP_RADIUS; dx <= MINIMAP_RADIUS; dx++)
        {
            int map_x = player_x + dx;
            int map_y = player_y + dy;

            int screen_x = (dx + MINIMAP_RADIUS) * MINIMAP_SCALE;
            int screen_y = (dy + MINIMAP_RADIUS) * MINIMAP_SCALE;

    if (map_y < 0 || map_y >= gen->parse->height)
        continue;

    if (map_x < 0)
        continue;

    if (!gen->parse->map[map_y])
        continue;

    int row_len = ft_strlen(gen->parse->map[map_y]);
    if (map_x >= row_len)
        continue;



            int color;
            if (gen->parse->map[map_y][map_x] == '1')
                color = 0xFFFFFF;
            else if (gen->parse->map[map_y][map_x] == '0')
                color = 0x161616;
            else
                continue;

            draw_minimap_tile_pixel(
                gen,
                screen_x,
                screen_y,
                color
            );
        }
    }
    int center = MINIMAP_RADIUS * MINIMAP_SCALE;
    draw_player_dot(gen, center, center);
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