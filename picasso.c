#include "./headers/cub3d.h"

int draw_arm(void *param)
{
	t_gen *gen;

	if (!param)
		return (0);
	gen = (t_gen *)param;
	if (!gen->arm)
		return (0);

	mlx_put_image_to_window(gen->mlx_data->mlx_ptr,gen->mlx_data->win_ptr,gen->arm,
        gen->mlx_data->win_width - gen->texture_data->arm_width,gen->mlx_data->win_height - gen->texture_data->arm_height);
	return (0);
}

void draw_minimap(t_gen *gen)
{
    int row;
    int col;
    int dx;
    int dy;
    int color;

    if (!gen || !gen->parse || !gen->parse->map)
        return;
    row = 0;
    while (gen->parse->map[row])
    {
        col = 0;
        while (gen->parse->map[row][col])
        {
            if (gen->parse->map[row][col] == '1')
                color = 0xFFFFFF;
            else if (gen->parse->map[row][col] == '0')
                color = 0x161616;
            else
            {
                col++;
                continue;
            }

            dy = 0;
            while (dy < MINIMAP_SCALE)
            {
                dx = 0;
                while (dx < MINIMAP_SCALE)
                {
                    copied_mlx_pixel_put(&gen->minimap->image,col * 
                        MINIMAP_SCALE + dx,row * MINIMAP_SCALE + dy,color);
                    dx++;
                }
                dy++;
            }
            col++;
        }
        row++;
    }
    draw_minimap_tile(gen,(int)gen->player->y,(int)gen->player->x,0xFFA500);
    mlx_put_image_to_window(gen->mlx_data->mlx_ptr,gen->mlx_data->win_ptr,
        gen->minimap->image.img,0,0);
}

void draw_minimap_tile(t_gen *gen, int row, int col, int color)
{
    int dx;
    int dy;

    dy = 0;
    while (dy < MINIMAP_SCALE)
    {
        dx = 0;
        while (dx < MINIMAP_SCALE)
        {
            copied_mlx_pixel_put(&gen->minimap->image,col * MINIMAP_SCALE + dx,row * MINIMAP_SCALE + dy,color);
            dx++;
        }
        dy++;
    }
}

void redraw_map_tiles(t_gen *gen, int y, int x, int prev[2])
{
    (void)prev;
    (void)x;
    (void)y;

    draw_minimap_tile(gen,prev[0],prev[1],0x161616);
    draw_minimap_tile( gen, y, x, 0xFFA500);
    draw_minimap(gen);        // redesenha mapa + player
    ciclope_dos_xman(gen);    // desenha o raio NOVO

    mlx_put_image_to_window(gen->mlx_data->mlx_ptr,gen->mlx_data->win_ptr,
        gen->minimap->image.img,0, 0);
}