#include "../headers/cub3d.h"

bool	is_out_of_bounds(t_gen *gen, int y, int x)
{
	if (y < 0 || y >= gen->parse->height)
		return (true);
	if (x < 0 || x >= (int)strlen(gen->parse->map[y]))
		return (true);
	return (false);
}

bool	is_blocked(t_gen *gen, int y, int x)
{
	if (gen->parse->map[y][x] == '1')
		return (true);
	if (gen->parse->map[y][x] == 'D')
		return (true);
	return (false);
}

bool	check_corner_collision(t_gen *gen, double next_y, double next_x,
		double radius)
{
	int	y;
	int	x;

	(void)radius;
	y = (int)next_y;
	x = (int)next_x;
	if (y < 0 || x < 0 || is_out_of_bounds(gen, y, x))
		return (true);
	if (is_blocked(gen, y, x))
		return (true);
	return (false);
}

bool	collision(t_gen *gen, double next_y, double next_x)
{
	double	radius;

	radius = 0.2;
	if (check_corner_collision(gen, next_y - radius, next_x - radius, radius))
		return (true);
	if (check_corner_collision(gen, next_y - radius, next_x + radius, radius))
		return (true);
	if (check_corner_collision(gen, next_y + radius, next_x - radius, radius))
		return (true);
	if (check_corner_collision(gen, next_y + radius, next_x + radius, radius))
		return (true);
	return (false);
}
