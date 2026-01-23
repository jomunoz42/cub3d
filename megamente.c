#include "./headers/cub3d.h"

void search_in_matrix(t_gen *gen, int character)
{
    int row = 0;
    while (gen->parse->map[row])
    {
        int col = 0;
        while (gen->parse->map[row][col])
        {
            if (gen->parse->map[row][col] == character)
            {
                gen->player->x = col + 0.5;
                gen->player->y = row + 0.5;

                gen->player->dir_x = 0;
                gen->player->dir_y = -1;
                gen->player->plane_x = 0.66;
                gen->player->plane_y = 0;
                return;
            }
            col++;
        }
        row++;
    }
}

int get_player_position(t_gen *gen)
{
    search_in_matrix(gen, 'N');
    return (0);
}

void	ciclope_dos_xman(t_gen *gen)
{
	double	ray_x;
	double	ray_y;
	double	step;
	int		map_x;
	int		map_y;
	int		px;
	int		py;

	if (!gen || !gen->player || !gen->parse || !gen->parse->map)
		return;

	ray_x = gen->player->x;
	ray_y = gen->player->y;
	step = 0.05;

	while (1)
	{
		map_x = (int)ray_x;
		map_y = (int)ray_y;

		if (map_y < 0 || map_x < 0
			|| !gen->parse->map[map_y]
			|| !gen->parse->map[map_y][map_x])
			break;
		if (gen->parse->map[map_y][map_x] == '1')
			break;
		px = (int)(ray_x * MINIMAP_SCALE);
		py = (int)(ray_y * MINIMAP_SCALE);

		if (px >= 0 && px < gen->minimap->width
			&& py >= 0 && py < gen->minimap->height)
			copied_mlx_pixel_put(&gen->minimap->image, px, py, 0xFF0000);

		ray_x += gen->player->dir_x * step;
		ray_y += gen->player->dir_y * step;
	}
}



