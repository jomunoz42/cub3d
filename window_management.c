#include "./headers/cub3d.h"
#include "headers/general.h"
#include "headers/mlx.h"

int window_init(t_gen *gen, int w, int h)
{
	gen->mlx_data->win_ptr = mlx_new_window(gen->mlx_data->mlx_ptr,
			gen->mlx_data->win_width, gen->mlx_data->win_height, "salve");
	if (!gen->mlx_data->win_ptr)
		return (1);
	gen->arm = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr, USER_HAND_XPM, &w,
			&h);
	if (!gen->arm)
		return (printf("Error: failed to load arm image\n"), 1);
	return (0);
}

int	start_window(t_gen *gen, char *argv)
{
	int		w;
	int		h;

	w = 0;
	h = 0;
	(void)argv;
	if (window_init(gen, w, h) == 1)
		return (printf("inutil animal\n"), 1);
	// genesis(gen);
	get_player_position(gen);
	// mlx_loop_hook(gen->mlx_data->mlx_ptr, draw_arm, gen); TENHO QUE COLOCAR O DRAW ARM EM OUTRO LUGAR
	gen->minimap->image.img = mlx_new_image(gen->mlx_data->mlx_ptr, gen->minimap->width, gen->minimap->height);
	gen->minimap->image.addr = mlx_get_data_addr(gen->minimap->image.img , &gen->minimap->image.bits_pixel, &gen->minimap->image.line_len, &gen->minimap->image.endian);
	mlx_put_image_to_window(gen->mlx_data->mlx_ptr,gen->mlx_data->win_ptr,gen->minimap->image.img,0, 0);
	mlx_hook(gen->mlx_data->win_ptr, 2, 1L << 0, key_press, gen);
	mlx_hook(gen->mlx_data->win_ptr, 3, 1L << 1, key_release, gen);
	mlx_loop_hook(gen->mlx_data->mlx_ptr, game_loop, gen);
	mlx_loop(gen->mlx_data->mlx_ptr);
	mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->arm);
	mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->minimap->image.img);
	return (0);
}
