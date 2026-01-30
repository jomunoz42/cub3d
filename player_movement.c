#include "./headers/cub3d.h"
#include "headers/general.h"


int game_loop(t_gen *gen)
{
	double nx = gen->player->x;
	double ny = gen->player->y;
	// int prev[2] = {(int)ny, (int)nx};

	// 🚶 movimento
	if (gen->kboard->key_w)
	{
		nx += gen->player->dir_x * MOVE_SPEED;
		ny += gen->player->dir_y * MOVE_SPEED;
	}
	if (gen->kboard->key_s)
	{
		nx -= gen->player->dir_x * MOVE_SPEED;
		ny -= gen->player->dir_y * MOVE_SPEED;
	}
	if (gen->kboard->key_a)
	{
		nx += gen->player->plane_x * MOVE_SPEED;
		ny += gen->player->plane_y * MOVE_SPEED;
	}
	if (gen->kboard->key_d)
	{
		nx -= gen->player->plane_x * MOVE_SPEED;
		ny -= gen->player->plane_y * MOVE_SPEED;
	}
	if (gen->kboard->key_right)
		rotate_player(gen, ROTATION_SPEED);
	if (gen->kboard->key_left)
		rotate_player(gen, -ROTATION_SPEED);

	// 🧱 colisão
	if (!collision(gen, ny, nx))
	{
		gen->player->x = nx;
		gen->player->y = ny;
	}
	draw_minimap(gen);   // limpa minimapa
	render_scene(gen);  // raycast + raios + paredes

	return (0);
}

