
#include "./headers/cub3d.h"

static void flood_from_player(t_gen *gen, char **copy, int x, int y)
{
    if (x < 0 || y < 0 || x >= gen->parse->width || y >= gen->parse->height)
        return ;
    if (copy[y][x] == '1' || copy[y][x] == 'F')
        return ;
    copy[y][x] = 'F';
    flood_from_player(gen, copy, x + 1, y);
    flood_from_player(gen, copy, x - 1, y);
    flood_from_player(gen, copy, x, y + 1);
    flood_from_player(gen, copy, x, y - 1);
}

static int	find_player_quadrant(t_gen *gen)
{
	if (gen->player->x < gen->parse->width / 2 && gen->player->y < gen->parse->height / 2)
		return (1);
	if (gen->player->x > gen->parse->width / 2 && gen->player->y < gen->parse->height / 2)
		return (2);
	if (gen->player->x < gen->parse->width / 2 && gen->player->y > gen->parse->height / 2)
		return (3);
	if (gen->player->x > gen->parse->width / 2 && gen->player->y > gen->parse->height / 2)
		return (4);
	return (0);
}

static t_quad_bounds get_quadrant_bounds(t_gen *gen, int quadrant)
{
	t_quad_bounds b;
	int	 		  mid_x;
    int 		  mid_y;

	mid_x = gen->parse->width / 2;
	mid_y = gen->parse->height / 2;
    b.start_x = 0;
    b.end_x = 0;
    b.start_y = 0;
    b.end_y = 0;
	if (quadrant == 1)
    {
        b.start_x = mid_x - 1;
        b.end_x   = 0;
        b.start_y = mid_y - 1;
        b.end_y   = 0;
    }
	else if (quadrant == 2)
    {
        b.start_x = gen->parse->width - 1;
        b.end_x   = mid_x;
        b.start_y = mid_y - 1;
        b.end_y   = 0;
    }
    else if (quadrant == 3)
    {
        b.start_x = mid_x - 1;
        b.end_x   = 0;
        b.start_y = gen->parse->height - 1;
        b.end_y   = mid_y;
    }
    else if (quadrant == 4)
    {
        b.start_x = gen->parse->width - 1;
        b.end_x   = mid_x;
        b.start_y = gen->parse->height - 1;
        b.end_y   = mid_y;
    }
	return (b);
}

static void get_quadrant_priority(int player_q, int order[4])
{
	if (player_q == 1)
		ft_memcpy(order, (int [4]){4, 3, 2, 1}, sizeof(int) * 4);
	else if (player_q == 2)
		ft_memcpy(order, (int [4]){3, 4, 1, 2}, sizeof(int) * 4);
	else if (player_q == 3)
		ft_memcpy(order, (int [4]){2, 1, 4, 3}, sizeof(int) * 4);
	else
		ft_memcpy(order, (int [4]){1, 2, 3, 4}, sizeof(int) * 4);
}

static int try_quadrant(t_gen *gen, char **copy, int quadrant)
{
	t_quad_bounds quad;
	int x;
	int y;

	quad = get_quadrant_bounds(gen, quadrant);
	y = quad.start_y;
	while (y >= quad.end_y)
	{
		x = quad.start_x;
		while(x >= quad.end_x)
		{
			if (copy[y][x] == 'F')
       		{
	            gen->enemy[gen->enemy_count].size = 40;
				gen->enemy[gen->enemy_count].x = x + 0.5;
				gen->enemy[gen->enemy_count].y = y + 0.5;
	            gen->enemy[gen->enemy_count].type = WINNING_STAR;
				gen->exit->active = true;
				return (1);
			}
			x--;
		}
		y--;
	}
	return (0);
}

void	set_valid_exit(t_gen *gen)
{
	char 		**copy;
	int			player_q;
	int 		order[4];
	int 		i;

	i = 0;
	copy = create_copy_map(gen->parse);
	flood_from_player(gen, copy, (int)gen->player->x, (int)gen->player->y);
	player_q = find_player_quadrant(gen);
	get_quadrant_priority(player_q, order);
	gen->exit->active = false;
	while (i < 4)
    {
        if (try_quadrant(gen, copy, order[i]))
        {
            free_double(copy);
            return;
        }
		i++;
    }
	free_double(copy);
}
