#include "./headers/cub3d.h"

typedef struct s_node
{
    int x;
    int y;
} t_node;

/* === Find Enemy Initial Position === */
void find_enemy_position(t_gen *gen, char c)
{
    int row = 0;
    while (gen->parse->map[row])
    {
        int col = 0;
        while (gen->parse->map[row][col])
        {
            if (gen->parse->map[row][col] == c)
            {
                gen->enemy->x = col + 0.5;
                gen->enemy->y = row + 0.5;
                return;
            }
            col++;
        }
        row++;
    }
}

/* === Draw Enemy on Minimap === */
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

/* === A* Callbacks === */
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

void update_enemy(t_gen *gen)
{
    t_node start = { (int)gen->enemy->x, (int)gen->enemy->y };
    t_node goal  = { (int)gen->player->x, (int)gen->player->y };

    ASPathNodeSource source = {0};
    source.nodeSize = sizeof(t_node);
    source.nodeNeighbors = nodeNeighbors;
    source.pathCostHeuristic = pathCostHeuristic;
    source.nodeComparator = nodeComparator;
    source.earlyExit = NULL; // optional

    ASPath path = ASPathCreate(&source, gen, &start, &goal);

    if (path && ASPathGetCount(path) > 1)
    {
        t_node *nextStep = ASPathGetNode(path, 1); // next node in path
        gen->enemy->x += (nextStep->x + 0.5 - gen->enemy->x) * gen->enemy->move_speed;
        gen->enemy->y += (nextStep->y + 0.5 - gen->enemy->y) * gen->enemy->move_speed;
    }

    if (path)
        ASPathDestroy(path);
}

bool enemy_visible(t_gen *gen)
{
    double dx = gen->enemy->x - gen->player->x;
    double dy = gen->enemy->y - gen->player->y;
    double distance = sqrt(dx*dx + dy*dy);

    double step_x = dx / distance * 0.1; // small step along line
    double step_y = dy / distance * 0.1;

    double x = gen->player->x;
    double y = gen->player->y;

    for (double i = 0; i < distance; i += 0.1)
    {
        int map_x = (int)x;
        int map_y = (int)y;
        if (gen->parse->map[map_y][map_x] == '1')
            return false; // wall blocks enemy
        x += step_x;
        y += step_y;
    }

    return true; // no wall blocking
}


void draw_enemy(t_gen *gen)
{
    if (!gen->enemy || !gen->enemy_tex)
        return;

    if (!enemy_visible(gen))
        return ;
    t_enemy *enemy = gen->enemy;
    t_texture *tex = gen->enemy_tex;

    double sprite_x = enemy->x - gen->player->x;
    double sprite_y = enemy->y - gen->player->y;

    double inv_det = 1.0 / (gen->player->plane_x * gen->player->dir_y - gen->player->dir_x * gen->player->plane_y);
    double transform_x = inv_det * (gen->player->dir_y * sprite_x - gen->player->dir_x * sprite_y);
    double transform_y = inv_det * (-gen->player->plane_y * sprite_x + gen->player->plane_x * sprite_y);

    if (transform_y <= 0)
        return; // Behind camera

    int sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x / transform_y));

    int sprite_height = abs((int)(WIN_HEIGHT / transform_y));
    int draw_start_y = -sprite_height / 2 + WIN_HEIGHT / 2;
    int draw_end_y = sprite_height / 2 + WIN_HEIGHT / 2;
    if (draw_start_y < 0) draw_start_y = 0;
    if (draw_end_y >= WIN_HEIGHT) draw_end_y = WIN_HEIGHT - 1;

    int sprite_width = abs((int)(WIN_HEIGHT / transform_y));
    int draw_start_x = -sprite_width / 2 + sprite_screen_x;
    int draw_end_x = sprite_width / 2 + sprite_screen_x;
    if (draw_start_x < 0) draw_start_x = 0;
    if (draw_end_x >= WIN_WIDTH) draw_end_x = WIN_WIDTH - 1;

    for (int stripe = draw_start_x; stripe < draw_end_x; stripe++)
    {
        int tex_x = (int)((stripe - draw_start_x) * tex->width / (draw_end_x - draw_start_x));

        for (int y = draw_start_y; y < draw_end_y; y++)
        {
            int d = y * 256 - WIN_HEIGHT * 128 + sprite_height * 128;
            int tex_y = ((d * tex->height) / sprite_height) / 256;
            int color = tex->data[tex_y * tex->width + tex_x];

            if ((color & 0x00FFFFFF) != 0)
                copied_mlx_pixel_put(gen->img_data, stripe, y, color);
        }
    }
}
