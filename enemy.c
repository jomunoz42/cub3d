#include "./headers/cub3d.h"

int count_enemies_in_map(t_gen *gen)
{
    int count;
    int row;
    int col;

    count = 0;
    row = 0;
    while (gen->parse->map[row])
    {
        col = 0;
        while (gen->parse->map[row][col])
        {
            if (gen->parse->map[row][col] == 'X'
                || gen->parse->map[row][col] == 'x'
                || gen->parse->map[row][col] == 'Z')
            {
                count++;
            }
            col++;
        }
        row++;
    }
    return (count);
}

void find_enemy_from_map(t_gen *gen, int i)
{
    for (int row = 0; gen->parse->map[row]; row++)
    {
        for (int col = 0; gen->parse->map[row][col]; col++)
        {
            if (gen->parse->map[row][col] == 'X')
            {
                gen->parse->map[row][col] = '0';
                gen->enemy[i].x = col + 0.5;
                gen->enemy[i].y = row + 0.5;
                gen->enemy[i].type = ENEMY_GHOST;
                return;
            }
            if (gen->parse->map[row][col] == 'x')
            {
                gen->parse->map[row][col] = '0';
                gen->enemy[i].x = col + 0.5;
                gen->enemy[i].y = row + 0.5;
                gen->enemy[i].type = ENEMY_CTHULHU;
                return;
            }
            if (gen->parse->map[row][col] == 'Z')
            {
                gen->parse->map[row][col] = '0';
                gen->enemy[i].x = col + 0.5;
                gen->enemy[i].y = row + 0.5;
                gen->enemy[i].type = ENEMY_SKELETON;
                return;
            }
        }
    }
}

void draw_enemy_minimap(t_gen *gen)
{
    int start_x = (int)gen->player->x - gen->minimap->zoom_level / 2;
    int start_y = (int)gen->player->y - gen->minimap->zoom_level / 2;

    int px = (gen->enemy->x - start_x) * MINIMAP_TILE_PIXELS;
    int py = (gen->enemy->y - start_y) * MINIMAP_TILE_PIXELS;

    if (px < 0 || py < 0 || px >= MINIMAP_PIXELS || py >= MINIMAP_PIXELS)
        return;

    for (int y = -3; y <= 3; y++)
        for (int x = -3; x <= 3; x++)
            copied_mlx_pixel_put(gen->img_data, px + x, py + y, 0xdb27c9);
}

int nodeComparator(void *node1, void *node2, void *context)
{
    (void)context;
    t_node *n1 = (t_node *)node1;
    t_node *n2 = (t_node *)node2;

    if (n1->x < n2->x) return -1;
    if (n1->x > n2->x) return 1;
    if (n1->y < n2->y) return -1;
    if (n1->y > n2->y) return 1;
    return 0;
}

void nodeNeighbors(ASNeighborList neighbors, void *currentNode, void *context)
{

    t_gen *gen = (t_gen *)context;
    t_node *node = (t_node *)currentNode;
    int dirs[4][2] = { {0,1}, {1,0}, {0,-1}, {-1,0} };

    for (int i = 0; i < 4; i++)
    {
        int nx = node->x + dirs[i][0];
        int ny = node->y + dirs[i][1];

        if (ny >= 0 && ny < gen->parse->height && nx >= 0 && nx < gen->parse->width)
        {
            if (gen->parse->map[ny][nx] != '1')
            {
                t_node neighbor = { nx, ny };
                ASNeighborListAdd(neighbors, &neighbor, 1.0f); // cost = 1
            }
        }
    }
}

float pathCostHeuristic(void *a, void *b, void *context)
{
    (void)context;
    t_node *n1 = (t_node *)a;
    t_node *n2 = (t_node *)b;
    return abs(n1->x - n2->x) + abs(n1->y - n2->y); // Manhattan distance
}

void update_enemy(t_gen *gen, int i)
{
    t_node start = { (int)gen->enemy[i].x, (int)gen->enemy[i].y };
    t_node goal  = { (int)gen->player->x, (int)gen->player->y };

    ASPathNodeSource source = {0};
    source.nodeSize = sizeof(t_node);
    source.nodeNeighbors = nodeNeighbors;
    source.pathCostHeuristic = pathCostHeuristic;
    source.nodeComparator = nodeComparator;
    source.earlyExit = NULL;

    ASPath path = ASPathCreate(&source, gen, &start, &goal);

    if (path && ASPathGetCount(path) > 0)
    {
        t_node *nextStep;

        double dx = gen->player->x - gen->enemy[i].x;
        double dy = gen->player->y - gen->enemy[i].y;
        double distance = sqrt(dx*dx + dy*dy);
        if (distance > 0.5 && ASPathGetCount(path) > 1)
            nextStep = ASPathGetNode(path, 1);
        else
        {
            t_node direct = { (int)gen->player->x, (int)gen->player->y };
            nextStep = &direct;
        }
        gen->enemy[i].x += (nextStep->x + 0.5 - gen->enemy[i].x) * gen->enemy[i].move_speed;
        gen->enemy[i].y += (nextStep->y + 0.5 - gen->enemy[i].y) * gen->enemy[i].move_speed;
    }
    if (path)
        ASPathDestroy(path);
}

bool enemy_visible(t_gen *gen, double *distance_out, int i)
{
    double dx = gen->enemy[i].x - gen->player->x;
    double dy = gen->enemy[i].y - gen->player->y;
    double distance = sqrt(dx*dx + dy*dy);

    if (distance_out)
        *distance_out = distance;

    if (distance > FOG_END) // Enemy is too far
        return (false);

    double step_x = dx / distance * 0.1;
    double step_y = dy / distance * 0.1;

    double x = gen->player->x;
    double y = gen->player->y;

    for (double i = 0; i < distance; i += 0.1)
    {
        int map_x = (int)x;
        int map_y = (int)y;
        if (gen->parse->map[map_y][map_x] == '1')
            return (false); // Wall blocks view
        x += step_x;
        y += step_y;
    }

    return true;
}

void update_enemy_animation(t_enemy *enemy, int i)
{
    int max_frames;
    int speed;

    if (enemy[i].type == ENEMY_GHOST)
    {
        max_frames = 4;
        speed = 10;
    }
    else if (enemy[i].type == ENEMY_CTHULHU)
    {
        max_frames = 2;
        speed = 25;
    }
    else if (enemy[i].type == ENEMY_SKELETON)
    {
        max_frames = 7;
        speed = 4;
    }
    else
        return;
    enemy[i].enemy_timer++;
    if (enemy[i].enemy_timer >= speed)
    {
        enemy[i].enemy_timer = 0;
        enemy[i].enemy_frame = (enemy[i].enemy_frame + 1) % max_frames;
    }
}

void draw_enemy(t_gen *gen, int i)
{
    if (!gen->enemy)
        return;
    if (gen->enemy[i].type == ENEMY_GHOST && !gen->ghost_enemy[0])
        return;
    if (gen->enemy[i].type == ENEMY_CTHULHU && !gen->cthulhu_enemy[0])
        return;
    if (gen->enemy[i].type == ENEMY_SKELETON && !gen->skeleton_enemy[0])
        return;

    double distance;
    if (!enemy_visible(gen, &distance, i))
        return;

    t_enemy   *enemy = &gen->enemy[i];
    t_texture *tex;

    if (enemy->type == ENEMY_GHOST)
        tex = gen->ghost_enemy[enemy->enemy_frame];
    else if (enemy->type == ENEMY_CTHULHU)
        tex = gen->cthulhu_enemy[enemy->enemy_frame];
    else if (enemy->type == ENEMY_SKELETON)
        tex = gen->skeleton_enemy[enemy->enemy_frame];
    else
        return;

    double sprite_x = enemy->x - gen->player->x;
    double sprite_y = enemy->y - gen->player->y;

    double inv_det = 1.0 / (gen->player->plane_x * gen->player->dir_y - gen->player->dir_x * gen->player->plane_y);
    double transform_x = inv_det * (gen->player->dir_y * sprite_x - gen->player->dir_x * sprite_y);
    double transform_y = inv_det * (-gen->player->plane_y * sprite_x + gen->player->plane_x * sprite_y);

    if (transform_y <= 0)
        return;

    int sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x / transform_y));
    int sprite_height = abs((int)(WIN_HEIGHT / transform_y));
    int draw_start_y = -sprite_height / 2 + WIN_HEIGHT / 2;
    int draw_end_y = sprite_height / 2 + WIN_HEIGHT / 2;
    if (draw_start_y < 0) draw_start_y = 0;
    if (draw_end_y >= WIN_HEIGHT) draw_end_y = WIN_HEIGHT - 1;
    int color = 0;
    int tex_y = 0;
    // int tex_x = 0;
    int d = 0;
    int sprite_width = sprite_height;
    int draw_start_x = -sprite_width / 2 + sprite_screen_x;
    int draw_end_x = sprite_width / 2 + sprite_screen_x;
    if (draw_start_x < 0) draw_start_x = 0;
    if (draw_end_x >= WIN_WIDTH) draw_end_x = WIN_WIDTH - 1;

    for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
    {
        int tex_x = (int)((stripe - draw_start_x) * tex->width / (draw_end_x - draw_start_x));

        for (int y = draw_start_y; y < draw_end_y; y++)
        {
            d = y * 256 - WIN_HEIGHT * 128 + sprite_height * 128;
            tex_y = ((d * tex->height) / sprite_height) / 256;
            color = tex->data[tex_y * tex->width + tex_x];
            if ((color & 0x00FFFFFF) != 0)
            {
                color = apply_fog(color, distance);
                copied_mlx_pixel_put(gen->img_data, stripe, y, color);
            }
        }
    }
}
