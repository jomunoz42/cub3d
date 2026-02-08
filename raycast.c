#include "./headers/cub3d.h"
#include "headers/general.h"

t_rayhit	castrate(t_gen *gen, double ray_direction_x, double ray_direction_y, bool interact)
{
	t_rayhit	hit;
	int			start_x;
	int			start_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		side_dist_x;
	double		side_dist_y;
	int			step_x;
	int			step_y;
	int			side;
	int			wall_hit;

	if (!gen || !gen->parse || !gen->parse->map)
	{
		ft_putstr_fd("ERROR: gen->parse is NULL\n", 2);
		exit(1);
	}
	start_x = (int)gen->player->x;
	start_y = (int)gen->player->y;
	delta_dist_x = fabs(1.0 / ray_direction_x);
	delta_dist_y = fabs(1.0 / ray_direction_y);
	side = 0;
	wall_hit = 0;
	if (ray_direction_x < 0)
	{
		step_x = -1;
		side_dist_x = (gen->player->x - start_x) * delta_dist_x;
	}
	else
	{
		step_x = 1;
		side_dist_x = (start_x + 1.0 - gen->player->x) * delta_dist_x;
	}
	if (ray_direction_y < 0)
	{
		step_y = -1;
		side_dist_y = (gen->player->y - start_y) * delta_dist_y;
	}
	else
	{
		step_y = 1;
		side_dist_y = (start_y + 1.0 - gen->player->y) * delta_dist_y;
	}
	while (!wall_hit)
	{
		if (side_dist_x < side_dist_y)
		{
			side_dist_x += delta_dist_x;
			start_x += step_x;
			side = 0;
		}
		else
		{
			side_dist_y += delta_dist_y;
			start_y += step_y;
			side = 1;
		}
		if (start_y < 0 || start_y >= gen->parse->height)
			break ;
		if (start_x < 0 || start_x >= (int)ft_strlen(gen->parse->map[start_y]))
			break ;
        char cell = gen->parse->map[start_y][start_x];
        if (cell == '1')
        {
            wall_hit = 1;
            hit.type = HIT_WALL;
        }
        else if (cell == 'D')
        {
            wall_hit = 1;
            hit.type = HIT_DOOR;
        }
        else if (cell == 'd')
        {
            if (interact)
            {
                hit.type = HIT_DOOR;
                break;
            }
            else
                continue;
        }
	}
	if (side == 0)
	{
		hit.dist = (start_x - gen->player->x + (1 - step_x) / 2.0)
			/ ray_direction_x;
		if (ray_direction_x > 0)
			hit.face = EAST;
		else
			hit.face = WEST;
	}
	else
	{
		hit.dist = (start_y - gen->player->y + (1 - step_y) / 2.0)
			/ ray_direction_y;
		if (ray_direction_y > 0)
			hit.face = NORTH;
		else
			hit.face = SOUTH;
	}
	hit.map_x = start_x;
	hit.map_y = start_y;
	hit.side = side;
	return (hit);
}

void	render_scene(t_gen *gen)
{
	double		camera_x;
	double		ray_direction_x;
	double		ray_direction_y;
	t_rayhit	hit;
	int			line_height;
	int			draw_start;
	int			draw_end;
		double wall_x;
		t_texture *tex;
	int			texture_x;
	int			d;
	int			texY;
	int			color;

	for (int x = 0; x < WIN_WIDTH; x++)
	{
		camera_x = gen->player->fov * x / (double)WIN_WIDTH - 1.0;
		ray_direction_x = gen->player->dir_x + gen->player->plane_x * camera_x;
		ray_direction_y = gen->player->dir_y + gen->player->plane_y * camera_x;
		hit = castrate(gen, ray_direction_x, ray_direction_y, 0);
		line_height = (int)(WIN_HEIGHT / hit.dist);
		draw_start = -line_height / 2 + WIN_HEIGHT / 2;
		draw_end = line_height / 2 + WIN_HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		if (draw_end >= WIN_HEIGHT)
			draw_end = WIN_HEIGHT - 1;
		if (hit.side == 0)
			wall_x = gen->player->y + hit.dist * ray_direction_y;
		else
			wall_x = gen->player->x + hit.dist * ray_direction_x;
		wall_x -= floor(wall_x);
        if (hit.type == HIT_WALL)
        {
            if (gen->flags->terror_mode)
			    tex = gen->terror_texture[hit.face];
		    else
			    tex = gen->texture[hit.face];
        }
        else if (hit.type == HIT_DOOR)
            tex = gen->door_texture;
		texture_x = (int)(wall_x * (double)tex->width);
		if ((hit.side == 0 && ray_direction_x < 0) || (hit.side == 1
				&& ray_direction_y > 0))
			texture_x = tex->width - texture_x - 1;
		for (int y = draw_start; y < draw_end; y++)
		{
			d = y * 256 - WIN_HEIGHT * 128 + line_height * 128;
			texY = ((d * tex->height) / line_height) / 256;
			color = tex->data[texY * tex->width + texture_x];
			if (gen->flags->terror_mode)
				color = apply_fog(color, hit.dist);
			copied_mlx_pixel_put(gen->img_data, x, y, color);
		}
		if (!gen->flags->terror_mode)
		{
			for (int y = 0; y < draw_start; y++)
				copied_mlx_pixel_put(gen->img_data, x, y,
					gen->texture_data->clng_color);
			for (int y = draw_end; y < WIN_HEIGHT; y++)
				copied_mlx_pixel_put(gen->img_data, x, y,
					gen->texture_data->flr_color);
		}
		else
		{
			for (int y = 0; y < draw_start; y++)
				copied_mlx_pixel_put(gen->img_data, x, y, BLACK_CLR);
			for (int y = draw_end; y < WIN_HEIGHT; y++)
				copied_mlx_pixel_put(gen->img_data, x, y, BLACK_CLR);
		}
	}
}
