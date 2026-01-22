#include "./headers/cub3d.h"

//colocar aqui as cenas de calculo
void search_in_matrix(t_gen *gen, int character)
{
    int x = 0;
    while (gen->parse->map[x])
    {
        int y = 0;
        while (gen->parse->map[x][y])
        {
            if (gen->parse->map[x][y] == character)
            {
                gen->player->x = x + 0.5;
                gen->player->y = y + 0.5;
                gen->player->dir_x = 0;
	            gen->player->dir_y = -1;
	            gen->player->plane_x = 0.66;
	            gen->player->plane_y = 0;
            }
            y++;
        }
        x++;
    }
}

int get_player_position(t_gen *gen)
{
    search_in_matrix(gen, 'N');

    return (0);
}

void ciclope_dos_xman(t_gen *gen)
{
	double	x;
	double	y;
	int		i;

	if (!gen || !gen->player)
		return;

	x = gen->player->x;
	y = gen->player->y;

	i = 0;
	while (i < 10)
	{
		int px = (int)(x * MINIMAP_SCALE);
		int py = (int)(y * MINIMAP_SCALE);

		px += MINIMAP_SCALE / 2;
		py += MINIMAP_SCALE / 2;

		if (px >= 0 && px < gen->minimap->width &&
			py >= 0 && py < gen->minimap->height)
		{
			copied_mlx_pixel_put(
				&gen->minimap->image,
				px,
				py,
				0xFF0000
			);
		}

		x += gen->player->dir_x * 0.1;
		y += gen->player->dir_y * 0.1;
		i++;
	}
}


