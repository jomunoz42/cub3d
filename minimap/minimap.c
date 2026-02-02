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

void draw_minimap_player(t_gen *gen)
{
    int center_tile = ZOOM_LEVEL / 2;

    int px = center_tile * MINIMAP_TILE_PIXELS;
    int py = center_tile * MINIMAP_TILE_PIXELS;

    for (int y = 0; y < MINIMAP_TILE_PIXELS; y++)
    {
        for (int x = 0; x < MINIMAP_TILE_PIXELS; x++)
        {
            copied_mlx_pixel_put(
                gen->img_data,
                px + x,
                py + y,
                0xFFA500
            );
        }
    }
}



void draw_minimap(t_gen *gen)
{
    int start_x = (int)gen->player->x - ZOOM_LEVEL / 2;
    int start_y = (int)gen->player->y - ZOOM_LEVEL / 2;

    for (int y = 0; y < ZOOM_LEVEL; y++)
    {
        for (int x = 0; x < ZOOM_LEVEL; x++)
        {
            int map_x = start_x + x;
            int map_y = start_y + y;

            if (map_x < 0 || map_y < 0 || map_y >= gen->parse->height)
                continue;

            int row_len = ft_strlen(gen->parse->map[map_y]);
            if (map_x >= row_len)
                continue;
            
            int color;
            if (gen->parse->map[map_y][map_x] == '1')
                color = 0xFFFFFF;
            else
                color = 0x161616;

            for (int py = 0; py < MINIMAP_TILE_PIXELS; py++)
                for (int px = 0; px < MINIMAP_TILE_PIXELS; px++)
                    copied_mlx_pixel_put(
                        gen->img_data,
                        x * MINIMAP_TILE_PIXELS + px,
                        y * MINIMAP_TILE_PIXELS + py,
                        color
                    );
        }
    }
    draw_minimap_player(gen);
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