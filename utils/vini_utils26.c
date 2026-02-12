#include "../headers/cub3d.h"

static int	init_texture_array(t_texture **array, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		array[i] = malloc(sizeof(t_texture));
		if (!array[i])
			return (0);
		array[i]->data = NULL;
		array[i]->height = 0;
		array[i]->width = 0;
		array[i]->img = NULL;
		i++;
	}
	return (1);
}

static int	init_enemy_textures(t_gen *gen)
{
	if (!init_texture_array(gen->ghost_enemy, 4))
		return (0);
	if (!init_texture_array(gen->cthulhu_enemy, 2))
		return (0);
	if (!init_texture_array(gen->skeleton_enemy, 8))
		return (0);
	return (1);
}

int	general_texture_init(t_gen *gen)
{
	if (!init_texture_array(gen->texture, 4))
		return (0);
	if (!init_texture_array(gen->terror_texture, 4))
		return (0);
	if (!init_enemy_textures(gen))
		return (0);
	return (1);
}