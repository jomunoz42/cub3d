#include "./headers/cub3d.h"
#include "headers/general.h"

void rotate_player(t_gen *gen, double angle)
{
	double oldDirX = gen->player->dir_x;
	double oldPlaneX = gen->player->plane_x;

	gen->player->dir_x = gen->player->dir_x * cos(angle)
		- gen->player->dir_y * sin(angle);
	gen->player->dir_y = oldDirX * sin(angle)
		+ gen->player->dir_y * cos(angle);

	gen->player->plane_x = gen->player->plane_x * cos(angle)
		- gen->player->plane_y * sin(angle);
	gen->player->plane_y = oldPlaneX * sin(angle)
		+ gen->player->plane_y * cos(angle);
}

int game_loop(t_gen *gen)
{

	double nx = gen->player->x;
	double ny = gen->player->y;

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
		nx -= gen->player->plane_x * MOVE_SPEED;
		ny -= gen->player->plane_y * MOVE_SPEED;
	}
	if (gen->kboard->key_d)
	{
		nx += gen->player->plane_x * MOVE_SPEED;
		ny += gen->player->plane_y * MOVE_SPEED;
	}
	if (gen->kboard->key_right)
		rotate_player(gen, ROTATION_SPEED);
	if (gen->kboard->key_left)
		rotate_player(gen, -ROTATION_SPEED);

	if (!collision(gen, ny, nx))
	{
		gen->player->x = nx;
		gen->player->y = ny;
	}
  genesis(gen);
  draw_arm(gen);
	draw_minimap(gen);   // limpa minimapa
	render_scene(gen);  // raycast + raios + paredes

	return (0);
}

