#include "./headers/cub3d.h"

// int draw_arm(void *param)
// {
// 	t_gen *gen;

// 	if (!param)
// 		return (0);
// 	gen = (t_gen *)param;
// 	if (!gen->arm)
// 		return (0);

// 	mlx_put_image_to_window(gen->mlx_data->mlx_ptr,gen->mlx_data->win_ptr,gen->arm,
//         gen->mlx_data->win_width - gen->texture_data->arm_width,gen->mlx_data->win_height - gen->texture_data->arm_height);
// 	return (0);
// }

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



void	genesis(t_gen *gen)
{
	int	color;
	int x, y;
	gen->img_data->img = mlx_new_image(gen->mlx_data->mlx_ptr,gen->mlx_data->win_width, gen->mlx_data->win_height);
	gen->img_data->addr = mlx_get_data_addr(gen->img_data->img,&gen->img_data->bits_pixel, &gen->img_data->line_len,&gen->img_data->endian);
	for (y = 0; y < gen->mlx_data->win_height; y++)
	{
		for (x = 0; x < gen->mlx_data->win_width; x++)
		{
			color = (y < gen->texture_data->horizon) ? gen->texture_data->clng_color : gen->texture_data->flr_color;
			copied_mlx_pixel_put(gen->img_data, x, y, color);
		}
	}
	mlx_put_image_to_window(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,
		gen->img_data->img, 0, 0);
	// mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->img_data->img);
}