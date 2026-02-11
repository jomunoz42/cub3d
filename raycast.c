#include "./headers/cub3d.h"
#include "headers/general.h"

static void	init_start(t_gen *gen)
{
	gen->dda->start_x = (int)gen->player->x;
	gen->dda->start_y = (int)gen->player->y;
	gen->dda->wall_hit = 0;
	gen->dda->side = 0;
}

static void	init_delta(t_gen *gen, double ray_x, double ray_y)
{
	gen->dda->delta_x = fabs(1.0 / ray_x);
	gen->dda->delta_y = fabs(1.0 / ray_y);
}

static void	init_step_x(t_gen *gen, double ray_x)
{
	if (ray_x < 0)
	{
		gen->dda->step_x = -1;
		gen->dda->side_x = (gen->player->x - gen->dda->start_x)
			* gen->dda->delta_x;
	}
	else
	{
		gen->dda->step_x = 1;
		gen->dda->side_x = (gen->dda->start_x + 1.0 - gen->player->x)
			* gen->dda->delta_x;
	}
}

static void	init_step_y(t_gen *gen, double ray_y)
{
	if (ray_y < 0)
	{
		gen->dda->step_y = -1;
		gen->dda->side_y = (gen->player->y - gen->dda->start_y)
			* gen->dda->delta_y;
	}
	else
	{
		gen->dda->step_y = 1;
		gen->dda->side_y = (gen->dda->start_y + 1.0 - gen->player->y)
			* gen->dda->delta_y;
	}
}

static void	dda_step(t_gen *gen)
{
	if (gen->dda->side_x < gen->dda->side_y)
	{
		gen->dda->side_x += gen->dda->delta_x;
		gen->dda->start_x += gen->dda->step_x;
		gen->dda->side = 0;
	}
	else
	{
		gen->dda->side_y += gen->dda->delta_y;
		gen->dda->start_y += gen->dda->step_y;
		gen->dda->side = 1;
	}
}

static int	check_hit(t_gen *gen, bool interact, t_rayhit *hit)
{
	char	cell;

	if (gen->dda->start_y < 0 || gen->dda->start_y >= gen->parse->height)
		return (1);
	if (gen->dda->start_x < 0
		|| gen->dda->start_x >= (int)ft_strlen(gen->parse->map[gen->dda->start_y]))
		return (1);
	cell = gen->parse->map[gen->dda->start_y][gen->dda->start_x];
	if (cell == '1')
	{
		hit->type = HIT_WALL;
		return (1);
	}
	if (cell == 'D')
	{
		hit->type = HIT_DOOR;
		return (1);
	}
	if (cell == 'd' && interact)
	{
		hit->type = HIT_DOOR;
		return (1);
	}
	return (0);
}

static void	finalize_hit(t_gen *gen, double ray_x, double ray_y, t_rayhit *hit)
{
	if (gen->dda->side == 0)
	{
		hit->dist = (gen->dda->start_x - gen->player->x + (1 - gen->dda->step_x)
				/ 2.0) / ray_x;
		if (ray_x > 0)
			hit->face = EAST;
		else
			hit->face = WEST;
	}
	else
	{
		hit->dist = (gen->dda->start_y - gen->player->y + (1 - gen->dda->step_y)
				/ 2.0) / ray_y;
		if (ray_y > 0)
			hit->face = NORTH;
		else
			hit->face = SOUTH;
	}
	hit->map_x = gen->dda->start_x;
	hit->map_y = gen->dda->start_y;
	hit->side = gen->dda->side;
}

t_rayhit	castrate(t_gen *gen, double ray_x, double ray_y, bool interact)
{
	t_rayhit	hit;

	if (!gen || !gen->parse || !gen->parse->map)
	{
		ft_putstr_fd("ERROR: gen->parse is NULL\n", 2);
		exit(1);
	}
	init_start(gen);
	init_delta(gen, ray_x, ray_y);
	init_step_x(gen, ray_x);
	init_step_y(gen, ray_y);
	while (!gen->dda->wall_hit)
	{
		dda_step(gen);
		if (check_hit(gen, interact, &hit))
			break ;
	}
	finalize_hit(gen, ray_x, ray_y, &hit);
	return (hit);
}

static void	calculate_ray_params(int x, t_player *player, double *camera_x,
		double *ray_dir_x, double *ray_dir_y)
{
	*camera_x = player->fov * x / (double)WIN_WIDTH - 1.0;
	*ray_dir_x = player->dir_x + player->plane_x * *camera_x;
	*ray_dir_y = player->dir_y + player->plane_y * *camera_x;
}

static void	calculate_wall_dimensions(double dist, int *line_h, int *draw_start,
		int *draw_end)
{
	*line_h = (int)(WIN_HEIGHT / dist);
	*draw_start = -*line_h / 2 + WIN_HEIGHT / 2;
	*draw_end = *line_h / 2 + WIN_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}

static void	calculate_wall_x(t_gen *gen, t_rayhit hit, double ray_dir_x,
		double ray_dir_y, double *wall_x)
{
	if (hit.side == 0)
		*wall_x = gen->player->y + hit.dist * ray_dir_y;
	else
		*wall_x = gen->player->x + hit.dist * ray_dir_x;
	*wall_x -= floor(*wall_x);
}

static void	get_wall_texture(t_gen *gen, t_rayhit hit, t_texture **tex)
{
	if (hit.type == HIT_WALL)
	{
		if (gen->flags->terror_mode)
			*tex = gen->terror_texture[hit.face];
		else
			*tex = gen->texture[hit.face];
	}
	else
	{
		if (gen->flags->terror_mode)
			*tex = gen->door_texture2;
		else
			*tex = gen->door_texture;
	}
}

static void	calculate_texture_x(t_rayhit hit, double ray_dir_x,
		double ray_dir_y, double wall_x, t_texture *tex, int *texture_x)
{
	*texture_x = (int)(wall_x * (double)tex->width);
	if ((hit.side == 0 && ray_dir_x < 0) || (hit.side == 1 && ray_dir_y > 0))
		*texture_x = tex->width - *texture_x - 1;
}

static void	draw_wall_slice(t_gen *gen, int x, int draw_start, int draw_end,
		int line_height, t_texture *tex, int texture_x, double hit_dist)
{
	int	y;
	int	d;
	int	texY;
	int	color;

	y = draw_start;
	while (y < draw_end)
	{
		d = y * 256 - WIN_HEIGHT * 128 + line_height * 128;
		texY = ((d * tex->height) / line_height) / 256;
		color = tex->data[texY * tex->width + texture_x];
		if (gen->flags->terror_mode)
			color = apply_fog(color, hit_dist);
		copied_mlx_pixel_put(gen->img_data, x, y, color);
		y++;
	}
}

static void	draw_ceiling_slice(t_gen *gen, int x, int draw_start)
{
	int	y;
	int	color;

	y = 0;
	if (gen->flags->terror_mode)
		color = BLACK_CLR;
	else
		color = gen->texture_data->clng_color;
	while (y < draw_start)
	{
		copied_mlx_pixel_put(gen->img_data, x, y, color);
		y++;
	}
}

static void	draw_floor_slice(t_gen *gen, int x, int draw_end)
{
	int	y;
	int	color;

	y = draw_end;
	if (gen->flags->terror_mode)
		color = BLACK_CLR;
	else
		color = gen->texture_data->flr_color;
	while (y < WIN_HEIGHT)
	{
		copied_mlx_pixel_put(gen->img_data, x, y, color);
		y++;
	}
}

void	render_scene(t_gen *gen)
{
	int			x;
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	t_rayhit	hit;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	t_texture	*tex;
	int			texture_x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		calculate_ray_params(x, gen->player, &camera_x, &ray_dir_x, &ray_dir_y);
		hit = castrate(gen, ray_dir_x, ray_dir_y, 0);
		gen->rayhit->zbuffer[x] = hit.dist;
		calculate_wall_dimensions(hit.dist, &line_height, &draw_start,
			&draw_end);
		calculate_wall_x(gen, hit, ray_dir_x, ray_dir_y, &wall_x);
		get_wall_texture(gen, hit, &tex);
		calculate_texture_x(hit, ray_dir_x, ray_dir_y, wall_x, tex, &texture_x);
		draw_wall_slice(gen, x, draw_start, draw_end, line_height, tex,
			texture_x, hit.dist);
		draw_ceiling_slice(gen, x, draw_start);
		draw_floor_slice(gen, x, draw_end);
		x++;
	}
}
