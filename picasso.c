#include "./headers/cub3d.h"

int get_pixel_color(t_gen *gen, int x, int y)
{
    char *pixel;
    int color;

    if (!gen->arm || !gen->arm->addr)
        return 0;

    if (x < 0 || x >= (int)gen->texture_data->arm_width || y < 0 || y >= (int)gen->texture_data->arm_height)
        return 0;
    pixel = gen->arm->addr + (y * gen->arm->line_len + x * (gen->arm->bits_pixel / 8));
    color = *(int *)pixel;
    return color;
}

int get_pixel_color_img(t_img_data *img, int x, int y)
{
    if (!img || !img->addr)
        return 0;
    if (x < 0 || x >= img->line_len / (img->bits_pixel / 8) || y < 0)
        return 0;

    char *pixel = img->addr + y * img->line_len + x * (img->bits_pixel / 8);
    return *(int *)pixel;
}


void draw_arm(t_gen *gen)
{
    if (!gen || !gen->arm)
        return;

    int start_x = gen->mlx_data->win_width - gen->texture_data->arm_width;
    int start_y = gen->mlx_data->win_height - gen->texture_data->arm_height;

    for (int y = 0; y < (int)gen->texture_data->arm_height; y++)
    {
        for (int x = 0; x < (int)gen->texture_data->arm_width; x++)
        {
            int color = get_pixel_color(gen, x, y);
            if (color != TRANSPARENT_COLOR)
                copied_mlx_pixel_put(gen->img_data, start_x + x, start_y + y, color);
        }
    }
}
