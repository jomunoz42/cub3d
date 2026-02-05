#include "./headers/cub3d.h"

void find_enemy_position(t_gen *gen, char c)
{
    int row = 0;

    while (gen->parse->map[row])
    {
        int col = 0;
        while (gen->parse->map[row][col])
        {
            if (gen->parse->map[row][col] == c)
            {
                gen->enemy->x = col + 0.5;
                gen->enemy->y = row + 0.5;
                return;
            }
            col++;
        }
        row++;
    }
}

void update_enemy(t_gen *gen)
{
    double direction_x;
    double direction_y;
    double dist;
    direction_x = gen->player->x - gen->enemy->x;
    direction_y = gen->player->y - gen->enemy->y;
    dist = sqrt(direction_x * direction_x + direction_y * direction_y);
    if (dist < 1.0)
        return;
    direction_x /= dist;
    direction_y /= dist;
    gen->enemy->x += direction_x * gen->enemy->move_speed;
    gen->enemy->y += direction_y * gen->enemy->move_speed;
}

void draw_enemy_minimap(t_gen *gen)
{
    int start_x;
    int start_y;
    int px;
    int py;
    int x;
    int y;

    start_x = (int)gen->player->x - gen->minimap->zoom_level / 2;
    start_y = (int)gen->player->y - gen->minimap->zoom_level / 2;

    px = (gen->enemy->x - start_x) * MINIMAP_TILE_PIXELS;
    py = (gen->enemy->y - start_y) * MINIMAP_TILE_PIXELS;

    if (px < 0 || py < 0
        || px >= MINIMAP_PIXELS
        || py >= MINIMAP_PIXELS)
        return;

    y = -3;
    while (y <= 3)
    {
        x = -3;
        while (x <= 3)
        {
            copied_mlx_pixel_put(
                gen->img_data,
                px + x,
                py + y,
                0xdb27c9
            );
            x++;
        }
        y++;
    }
}



void draw_enemy(t_gen *gen)
{
    int x;
    int y;

    y = 0;
    while (y < gen->enemy->size)
    {
        x = 0;
        while (x < gen->enemy->size)
        {
            copied_mlx_pixel_put(
                gen->img_data,
                (int)gen->enemy->x + x,
                (int)gen->enemy->y + y,
                0xdb27c9
            );
            x++;
        }
        y++;
    }
}
