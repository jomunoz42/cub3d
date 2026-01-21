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

// void mini_minimap(t_gen *gen)
// {

// }

int get_player_position(t_gen *gen)
{
    search_in_matrix(gen, 'N');

    return (0);
}

