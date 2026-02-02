#include "./headers/cub3d.h"
#include "headers/general.h"
#include "headers/mlx.h"

int window_init(t_gen *gen, int w, int h)
{
	gen->mlx_data->win_ptr = mlx_new_window(gen->mlx_data->mlx_ptr,
			gen->mlx_data->win_width, gen->mlx_data->win_height, "salve");
	if (!gen->mlx_data->win_ptr)
		return (1);
	gen->arm->img = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr, USER_HAND_XPM, &w,
			&h);
	if (!gen->arm->img)
		return (printf("Error: failed to load arm image\n"), 1);
	return (0);
}

int start_window(t_gen *gen, char *argv)
{
    (void)argv;

    if (window_init(gen, 0, 0) == 1)
        return (printf("inutil animal\n"), 1);
    get_player_position(gen);
    gen->img_data->img = mlx_new_image(gen->mlx_data->mlx_ptr,gen->mlx_data->win_width,gen->mlx_data->win_height);
    gen->img_data->addr = mlx_get_data_addr(gen->img_data->img,&gen->img_data->bits_pixel,&gen->img_data->line_len,&gen->img_data->endian);
	gen->img_data->height = gen->mlx_data->win_height;
	gen->img_data->width = gen->mlx_data->win_width;
    mlx_hook(gen->mlx_data->win_ptr, 2, 1L << 0, key_press, gen);
    mlx_hook(gen->mlx_data->win_ptr, 3, 1L << 1, key_release, gen);

    mlx_loop_hook(gen->mlx_data->mlx_ptr, game_loop, gen);
    mlx_loop(gen->mlx_data->mlx_ptr);

    return 0;
}
