#include "./headers/cub3d.h"
#include "headers/general.h"

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
	if (gen->kboard->key_right)
	{
        rotate_player(gen, ROTATION_SPEED);
    }
	if (gen->kboard->key_left)
		rotate_player(gen, -ROTATION_SPEED);
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
