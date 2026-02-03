#include "./headers/cub3d.h"

t_rayhit cast_ray(t_gen *gen, double rayDirX, double rayDirY)
{
    if (!gen || !gen->parse || !gen->parse->map)
    {
        fprintf(stderr, "ERROR: gen->parse is NULL\n");
        exit(1);
    }

    t_rayhit hit;

    int start_x = (int)gen->player->x;
    int start_y = (int)gen->player->y;

    double deltaDistX = fabs(1.0 / rayDirX);
    double deltaDistY = fabs(1.0 / rayDirY);

    double sideDistX;
    double sideDistY;

    int stepX;
    int stepY;
    int side = 0;
    int wall_hit = 0;
    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (gen->player->x - start_x) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (start_x + 1.0 - gen->player->x) * deltaDistX;
    }

    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (gen->player->y - start_y) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (start_y + 1.0 - gen->player->y) * deltaDistY;
    }
    while (!wall_hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            start_x += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            start_y += stepY;
            side = 1;
        }
        if (start_y < 0 || start_y >= gen->parse->height)
            break;
        if (start_x < 0 || start_x >= (int)ft_strlen(gen->parse->map[start_y]))
            break;
        if (gen->parse->map[start_y][start_x] == '1')
            wall_hit = 1;
    }
    if (side == 0)
        hit.dist = (start_x - gen->player->x + (1 - stepX) / 2.0) / rayDirX;
    else
        hit.dist = (start_y - gen->player->y + (1 - stepY) / 2.0) / rayDirY;

    hit.mapX = start_x;
    hit.mapY = start_y;
    hit.side = side;

    return hit;
}


void render_scene(t_gen *gen)
{
    for (int x = 0; x < WIN_WIDTH; x++)
    {
        double cameraX = 2.0 * x / (double)WIN_WIDTH - 1.0;
        double rayDirX = gen->player->dir_x + gen->player->plane_x * cameraX;
        double rayDirY = gen->player->dir_y + gen->player->plane_y * cameraX;

        t_rayhit hit = cast_ray(gen, rayDirX, rayDirY);

        int lineHeight = (int)(WIN_HEIGHT / hit.dist);
        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        int drawEnd   = lineHeight / 2 + WIN_HEIGHT / 2;

        if (drawStart < 0) drawStart = 0;
        if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

        int color = (hit.side == 0) ? 0xAAAAAA : 0x777777;

        for (int y = drawStart; y < drawEnd; y++)
            copied_mlx_pixel_put(gen->img_data, x, y, color);

        for (int y = 0; y < drawStart; y++)
            copied_mlx_pixel_put(gen->img_data, x, y, gen->texture_data->clng_color);
        for (int y = drawEnd; y < WIN_HEIGHT; y++)
            copied_mlx_pixel_put(gen->img_data, x, y, gen->texture_data->flr_color);
    }
}
