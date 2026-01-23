#include "./headers/cub3d.h"
#include "headers/general.h"
#include "headers/mlx.h"

void	genesis(t_gen *gen)
{
	int	color;

	int x, y;
	gen->img_data->img = mlx_new_image(gen->mlx_data->mlx_ptr,
			gen->mlx_data->window_width, gen->mlx_data->window_height);
	gen->img_data->addr = mlx_get_data_addr(gen->img_data->img,
			&gen->img_data->bits_per_pixel, &gen->img_data->line_len,
			&gen->img_data->endian);
	for (y = 0; y < gen->mlx_data->window_height; y++)
	{
		for (x = 0; x < gen->mlx_data->window_width; x++)
		{
			color = (y < gen->texture_data->horizon) ? gen->texture_data->clng_color : gen->texture_data->flr_color;
			copied_mlx_pixel_put(gen->img_data, x, y, color);
		}
	}
	mlx_put_image_to_window(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,
		gen->img_data->img, 0, 0);
	mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->img_data->img);
}

int game_loop(t_gen *gen)
{
	double nx = gen->player->x;
	double ny = gen->player->y;
	int prev[2] = {(int)ny, (int)nx};

    if (gen->kboard->key_w) 
		ny -= MOVE_SPEED;
    if (gen->kboard->key_s) 
		ny += MOVE_SPEED;
    if (gen->kboard->key_a) 
		nx -= MOVE_SPEED;
    if (gen->kboard->key_d) 
		nx += MOVE_SPEED;
    if (nx != prev[1] || ny != prev[0])
    {
        if (!collision(gen, ny, nx))
        {
            gen->player->x = nx;
            gen->player->y = ny;
            redraw_map_tiles(gen, ny, nx, prev);
        }
    }
    return (0);
}

int	start_window(t_gen *gen)
{
	int		w;
	int		h;

	w = 0;
	h = 0;
	gen->mlx_data->win_ptr = mlx_new_window(gen->mlx_data->mlx_ptr,
			gen->mlx_data->window_width, gen->mlx_data->window_height, "salve");
	if (!gen->mlx_data->win_ptr)
		return (1);
	gen->arm = mlx_xpm_file_to_image(gen->mlx_data->mlx_ptr, USER_HAND_XPM, &w,
			&h);
	if (!gen->arm)
		return (printf("Error: failed to load arm image\n"), 1);
	genesis(gen);
	mlx_loop_hook(gen->mlx_data->mlx_ptr, draw_arm, gen);
	gen->minimap->image.img = mlx_new_image(gen->mlx_data->mlx_ptr, gen->minimap->width, gen->minimap->height);
	gen->minimap->image.addr = mlx_get_data_addr(gen->minimap->image.img , &gen->minimap->image.bits_per_pixel, &gen->minimap->image.line_len, &gen->minimap->image.endian);
	draw_minimap(gen);
	// ciclope_dos_xman(gen);
	// mlx_put_image_to_window(gen->mlx_data->mlx_ptr,gen->mlx_data->win_ptr,gen->minimap->image.img,0, 0);
	mlx_hook(gen->mlx_data->win_ptr, 2, 1L << 0, key_press, gen);
	mlx_hook(gen->mlx_data->win_ptr, 3, 1L << 1, key_release, gen);
	mlx_loop_hook(gen->mlx_data->mlx_ptr, game_loop, gen);

	mlx_loop(gen->mlx_data->mlx_ptr);
	mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->arm);
	mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->minimap->image.img);
	return (0);
}
