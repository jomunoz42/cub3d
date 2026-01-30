#include "./headers/cub3d.h"

t_rayhit cast_ray(t_gen *gen, double rayDirX, double rayDirY)
{
    t_rayhit hit;

    int mapX = (int)gen->player->x;
    int mapY = (int)gen->player->y;

    double sideDistX;
    double sideDistY;
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);

    int stepX;
    int stepY;
    int side;

    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (gen->player->x - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - gen->player->x) * deltaDistX;
    }

    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (gen->player->y - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - gen->player->y) * deltaDistY;
    }

    int wall_hit = 0;
    while (!wall_hit)
    {
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        if (gen->parse->map[mapY][mapX] == '1')
            wall_hit = 1;
    }

    if (side == 0)
        hit.dist = (mapX - gen->player->x + (1 - stepX) / 2) / rayDirX;
    else
        hit.dist = (mapY - gen->player->y + (1 - stepY) / 2) / rayDirY;

    hit.mapX = mapX;
    hit.mapY = mapY;
    hit.side = side;
    return (hit);
}

void draw_ray_debug(t_gen *gen, t_rayhit hit)
{
    int px0 = gen->player->x * MINIMAP_SCALE;
    int py0 = gen->player->y * MINIMAP_SCALE;
    int px1 = (hit.mapX + 0.5) * MINIMAP_SCALE;
    int py1 = (hit.mapY + 0.5) * MINIMAP_SCALE;

    ciclope_dos_xman(&gen->minimap->image, px0, py0, px1, py1, 0xFF0000);
}

void render_scene(t_gen *gen)
{
    // 1️⃣ limpa a imagem da cena
    gen->img_data->img = mlx_new_image(
        gen->mlx_data->mlx_ptr,
        WIN_WIDTH,
        WIN_HEIGHT
    );
    gen->img_data->addr = mlx_get_data_addr(
        gen->img_data->img,
        &gen->img_data->bits_pixel,
        &gen->img_data->line_len,
        &gen->img_data->endian
    );

    
    for (int x = 0; x < WIN_WIDTH; x++)
    {
        double cameraX = 2.0 * x / (double)WIN_WIDTH - 1.0;
        double rayDirX = gen->player->dir_x + gen->player->plane_x * cameraX;
        double rayDirY = gen->player->dir_y + gen->player->plane_y * cameraX;

        // 🔥 AQUI nasce o raio
        t_rayhit hit = cast_ray(gen, rayDirX, rayDirY);

        // 🔴 DEBUG NO MINIMAPA (AQUI!!)
        // draw_ray_debug(gen, hit);

        int lineHeight = (int)(WIN_HEIGHT / hit.dist);

        int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
        int drawEnd   =  lineHeight / 2 + WIN_HEIGHT / 2;

        if (drawStart < 0) drawStart = 0;
        if (drawEnd >= WIN_HEIGHT) drawEnd = WIN_HEIGHT - 1;

        int color = (hit.side == 0) ? 0xAAAAAA : 0x777777;

        for (int y = drawStart; y < drawEnd; y++)
            copied_mlx_pixel_put(gen->img_data, x, y, color);
    }

    // 2️⃣ manda a cena pra janela
    mlx_put_image_to_window(
        gen->mlx_data->mlx_ptr,
        gen->mlx_data->win_ptr,
        gen->img_data->img,
        0, 0
    );

    mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->img_data->img);
}
