#include "cub3d.h"

t_parsing *parsing_init(void)
{
    t_parsing *new;

    new = malloc(sizeof(t_parsing));
    if (!new)
        return (NULL);
    new->textures_info = NULL;
    return (new);
}