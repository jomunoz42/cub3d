#include "./headers/cub3d.h"
#include "headers/general.h"

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

void	calculate_ray_params(int x, t_player *player, double *camera_x, double *ray_dir_x, double *ray_dir_y)
{
	*camera_x = player->fov * x / (double)WIN_WIDTH - 1.0;
	*ray_dir_x = player->dir_x + player->plane_x * *camera_x;
	*ray_dir_y = player->dir_y + player->plane_y * *camera_x;
}

void	calculate_wall_dimensions(double dist, int *line_h, int *draw_start,int *draw_end)
{
	*line_h = (int)(WIN_HEIGHT / dist);
	*draw_start = -*line_h / 2 + WIN_HEIGHT / 2;
	*draw_end = *line_h / 2 + WIN_HEIGHT / 2;
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}

void	calculate_wall_x(t_gen *gen, t_rayhit hit, double ray_dir_x,double ray_dir_y, double *wall_x)
{
	if (hit.side == 0)
		*wall_x = gen->player->y + hit.dist * ray_dir_y;
	else
		*wall_x = gen->player->x + hit.dist * ray_dir_x;
	*wall_x -= floor(*wall_x);
}

void	get_wall_texture(t_gen *gen, t_rayhit hit, t_texture **tex)
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

void	calculate_texture_x(t_rayhit hit, double ray_dir_x, double ray_dir_y, double wall_x, t_texture *tex, int *texture_x)
{
	*texture_x = (int)(wall_x * (double)tex->width);
	if ((hit.side == 0 && ray_dir_x < 0) || (hit.side == 1 && ray_dir_y > 0))
		*texture_x = tex->width - *texture_x - 1;
}

void	draw_wall_slice(t_gen *gen, int x, int draw_start, int draw_end,int line_height, t_texture *tex, int texture_x, double hit_dist)
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

void	draw_ceiling_slice(t_gen *gen, int x, int draw_start)
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

void	draw_floor_slice(t_gen *gen, int x, int draw_end)
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
