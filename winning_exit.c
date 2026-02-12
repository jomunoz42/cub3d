
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
    {
        order[0] = 4;
        order[1] = 3;
        order[2] = 2;
        order[3] = 1;
    }
    else if (player_q == 2)
    {
        order[0] = 3;
        order[1] = 4;
        order[2] = 1;
        order[3] = 2;
    }
    else if (player_q == 3)
    {
        order[0] = 2;
        order[1] = 1;
        order[2] = 4;
        order[3] = 3;
    }
    else
    {
        order[0] = 1;
        order[1] = 2;
        order[2] = 3;
        order[3] = 4;
    }
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
                gen->enemy[gen->enemy_count].move_speed = 0;
	            gen->enemy[gen->enemy_count].size = 20;
	            gen->enemy[gen->enemy_count].enemy_frame = 0;
	            gen->enemy[gen->enemy_count].enemy_timer = 0;
				gen->enemy[gen->enemy_count].x = x;
				gen->enemy[gen->enemy_count].y = y;
	            gen->enemy[gen->enemy_count].type = WINNING_STAR;
				gen->exit.active = true;
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
	gen->exit.active = false;
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


// TO IMPLEMENT


// void	    set_valid_exit(t_gen *gen);

//makefile
// winning_exit.c


// typedef struct s_exit
// {
//     bool 	active;
// } 			t_exit;


// t_texture		*winning_exit[3];
// t_exit 			exit;

// typedef struct s_quad_bounds
// {
//     int 	start_x;
//     int 	end_x;
//     int 	start_y;
//     int 	end_y;
// }   		t_quad_bounds;

// typedef enum e_enemy_type
// {
//     ENEMY_GHOST,
//     ENEMY_CTHULHU,
//     ENEMY_SKELETON,
//     ENEMY_SKELETON2,
// 	WINNING_STAR
// } t_enemy_type;



//    wall_textures_init


// char	*star_xpm[3];

// star_xpm[0] = ft_strdup("imgs/star_1.xpm");
// star_xpm[1] = ft_strdup("imgs/star_2.xpm");
// star_xpm[2] = ft_strdup("imgs/star_3.xpm");

// if (i < 3)
// 		free(star_xpm[i]);


//   general_texture_init


// for (int i = 0; i < 3; i++)
// {
// 	gen->winning_exit[i] = malloc(sizeof(t_texture));
// 	if (!gen->winning_exit[i])
// 		return (0);
// 	gen->winning_exit[i]->data = NULL;
// 	gen->winning_exit[i]->height = 0;
// 	gen->winning_exit[i]->width = 0;
// 	gen->winning_exit[i]->img = NULL;
// }


// enemy_init


// gen->enemy = malloc(sizeof(t_enemy) * (gen->enemy_count + 1));
// 	if (!gen->enemy)
// 		return (0);

// 	gen->enemy[i].move_speed = 0;
// 	gen->enemy[i].size = 20;
// 	gen->enemy[i].x = 0;
// 	gen->enemy[i].y = 0;
// 	gen->enemy[i].enemy_frame = 0;
// 	gen->enemy[i].enemy_timer = 0;
// 	gen->enemy[i].type = WINNING_STAR;


// change to L in map validation


// key_press

	// if (gen->flags->terror_mode)
	// 	{
	// 		if (gen->exit.active == false)
	// 			set_valid_exit(gen);
	// 	}
	// 	else if (!gen->flags->terror_mode)
	// 		gen->exit.active = false;



// void find_enemy_from_map(t_gen *gen, int i)

//     static bool flag;

//       if (gen->parse->map[row][col] == 'Z')
    
//                 flag = !flag;
//                 gen->parse->map[row][col] = '0';
//                 gen->enemy[i].x = col + 0.5;
//                 gen->enemy[i].y = row + 0.5;
//                 if (flag)
//                     gen->enemy[i].type = ENEMY_SKELETON;
//                 else if (!flag)
//                     gen->enemy[i].type = ENEMY_SKELETON2;
//                 return;


//    draw_enemy

    // if (gen->enemy[i].type == ENEMY_SKELETON2 && !gen->skeleton_enemy[0])
    //     return;
    // if (gen->enemy[i].type == WINNING_STAR && (!gen->winning_exit[0] || !gen->exit.active))
    //     return;

    // else if (enemy->type == ENEMY_SKELETON2)
    //     tex = gen->skeleton_enemy[enemy->enemy_frame];
    // else if (enemy->type == WINNING_STAR)
    //     tex = gen->winning_exit[enemy->enemy_frame];


// void update_enemy_animation(t_enemy *enemy, int i)

    // else if (enemy[i].type == ENEMY_SKELETON2)
    // {
    //     max_frames = 3;
    //     speed = 6;
    // }
    // else if (enemy[i].type == WINNING_STAR)
    // {
    //     max_frames = 3;
    //     speed = 3;
    // }


//    int	game_loop(t_gen *gen)


// in the while that draws enemy:
// 		if (!gen->flags->terror_mode && (gen->enemy[i].type == ENEMY_SKELETON
// 			|| gen->enemy[i].type == ENEMY_SKELETON2))

// after that loop
// if (gen->exit.active)
// {
//     update_enemy_animation(gen->enemy, gen->enemy_count);
//     draw_enemy(gen, gen->enemy_count);
// }

// in death trigger
// if (distance <= 0.65 && gen->flags->terror_mode && i == gen->enemy_count)
// 		{
// 			printf("YOU WIN\n");
// 			super_duper_hiper_free();
// 			exit(1);
// 		}
// 		else if (distance <= 0.65 && gen->flags->terror_mode)
// 		{
// 			printf("You are dead\n");
// 			super_duper_hiper_free();
// 			exit(1);
// 		}