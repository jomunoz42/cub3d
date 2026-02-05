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


#define FOV_DEG 66.0
#define FOV_RAD (FOV_DEG * M_PI / 180.0)

void draw_enemy(t_gen *gen)
{
    double dx;
    double dy;
    double dist;
    double enemy_dir_x;
    double enemy_dir_y;
    double dot;
    double fov_limit;
    int screen_x;
    int screen_y;
    int x;
    int y;

    dx = gen->enemy->x - gen->player->x;
    dy = gen->enemy->y - gen->player->y;

    dist = sqrt(dx * dx + dy * dy);
    if (dist <= 0.01)
        return;

    enemy_dir_x = dx / dist;
    enemy_dir_y = dy / dist;

    dot = enemy_dir_x * gen->player->dir_x
        + enemy_dir_y * gen->player->dir_y;

    fov_limit = cos((66.0 * M_PI / 180.0) / 2.0);
    if (dot < fov_limit)
        return; // ❌ outside FOV

    screen_x = gen->mlx_data->win_width / 2 + (int)(dx * 50);
    screen_y = gen->mlx_data->win_height / 2 + (int)(dy * 50);

    y = 0;
    while (y < gen->enemy->size)
    {
        x = 0;
        while (x < gen->enemy->size)
        {
            copied_mlx_pixel_put(
                gen->img_data,
                screen_x + x,
                screen_y + y,
                0xdb27c9
            );
            x++;
        }
        y++;
    }
}



