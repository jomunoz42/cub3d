#include "./headers/cub3d.h"

void search_in_matrix(t_gen *gen, int character)
{
    int row = 0;
    if (!gen || !gen->parse || !gen->parse->map || !gen->parse->map[0][0])
        return ;
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
