#include "./headers/cub3d.h"
#include "headers/general.h"
#include "headers/mlx.h"

void	rotate_player(t_gen *gen, double angle)
{
	double	first_direction_x;
	double	first_plane_x;

	first_direction_x = gen->player->dir_x;
	first_plane_x = gen->player->plane_x;
	gen->player->dir_x = gen->player->dir_x * cos(angle) - gen->player->dir_y
		* sin(angle);
	gen->player->dir_y = first_direction_x * sin(angle) + gen->player->dir_y
		* cos(angle);
	gen->player->plane_x = gen->player->plane_x * cos(angle)
		- gen->player->plane_y * sin(angle);
	gen->player->plane_y = first_plane_x * sin(angle) + gen->player->plane_y
		* cos(angle);
}

void	apply_player_movement(t_gen *gen, double move_x, double move_y,
		double nx, double ny)
{
	if (gen->kboard->tab)
	{
		open_close_door(gen);
		gen->kboard->tab = false;
	}
	if (gen->kboard->key_right)
		rotate_player(gen, gen->player->rotate_speed);
	if (gen->kboard->key_left)
		rotate_player(gen, -gen->player->rotate_speed);
	if (!collision(gen, gen->player->y, nx + move_x))
		gen->player->x += move_x;
	if (!collision(gen, ny + move_y, gen->player->x))
		gen->player->y += move_y;
	if (!gen->flags->terror_mode && !gen->kboard->control_left)
	{
		if (!gen->kboard->shift_left)
			gen->player->move_speed = 0.05;
	}
}

void	update_player(t_gen *gen)
{
	double	nx;
	double	ny;
	double	move_x;
	double	move_y;

	nx = gen->player->x;
	ny = gen->player->y;
	calculate_player_movement(gen, &move_x, &move_y);
	apply_player_movement(gen, move_x, move_y, nx, ny);
}

int	game_loop(t_gen *gen)
{
	double	dx;
	double	dy;
	double	distance;
	int		i;

	update_player(gen);
	i = 0;
	while (i < gen->enemy_count)
	{
		gen->enemy[i].move_speed = 0.02;
		// if (gen->enemy[i].type != ENEMY_SKELETON)
		// 	update_enemy(gen, i);
		update_enemy_animation(gen->enemy, i);
		i++;
	}
	clear_image(gen->img_data, 0x000000);
	render_scene(gen);
	i = 0;
	while (i < gen->enemy_count)
	{
		if (!gen->flags->terror_mode && gen->enemy[i].type == ENEMY_SKELETON)
			draw_enemy(gen, i);
		if (gen->flags->terror_mode)
			draw_enemy(gen, i);
		i++;
	}
	mouse_looking(gen);
	if (!gen->flags->terror_mode && gen->flags->minimap)
		draw_minimap(gen);
	if (!gen->flags->terror_mode)
		draw_arm(gen);
	else
		draw_terror_arm(gen);
	apply_vignette_to_image(gen, gen->img_data);
	mlx_put_image_to_window(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr,
		gen->img_data->img, 0, 0);
	if (gen->flags->info && !gen->flags->terror_mode)
		print_info(gen);
	i = 0;
	while (i < gen->enemy_count)
	{
		dx = gen->enemy[i].x - gen->player->x;
		dy = gen->enemy[i].y - gen->player->y;
		distance = sqrt(dx * dx + dy * dy);
		if (distance <= 0.65 && gen->flags->terror_mode)
		{
			printf("You are dead\n");
			super_duper_hiper_free();
			exit(1);
		}
		i++;
	}
	return (0);
}
