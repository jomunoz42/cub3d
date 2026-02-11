#include "./headers/cub3d.h"
#include "headers/mlx.h"

int	handle_exit(int keysys)
{
	if (keysys == XK_Escape)
		return (super_duper_hiper_free(), 1);
	return (0);
}

void free_images_and_textures(t_gen *gen)
{
    if (gen->img_data)
    {
        if (gen->img_data->vignette)
            free(gen->img_data->vignette);

        if (gen->img_data->img && gen->mlx_data && gen->mlx_data->mlx_ptr)
            mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->img_data->img);
    }

    for (int i = 0; i < 4; i++)
    {
        if (gen->texture[i])
        {
            if (gen->mlx_data && gen->mlx_data->mlx_ptr)
                mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->texture[i]->img);
            free(gen->texture[i]);
        }
        if (gen->terror_texture[i])
            free(gen->terror_texture[i]);
    }

    if (gen->enemy_tex && gen->mlx_data)
    {
        free_texture(gen->mlx_data->mlx_ptr, gen->enemy_tex);
        gen->enemy_tex = NULL;
    }
}

void free_game_objects(t_gen *gen)
{
    if (gen->terror_arm)
    {
        if (gen->terror_arm->img && gen->mlx_data && gen->mlx_data->mlx_ptr)
            mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->terror_arm->img);
        free(gen->terror_arm);
    }

    if (gen->arm)
    {
        if (gen->arm->img && gen->mlx_data && gen->mlx_data->mlx_ptr)
            mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->arm->img);
        free(gen->arm);
    }

    if (gen->minimap)
    {
        if (gen->minimap->image.img && gen->mlx_data && gen->mlx_data->mlx_ptr)
            mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->minimap->image.img);
        if (gen->minimap->map)
            ft_free_matrix(gen->minimap->map);
        free(gen->minimap);
    }

    if (gen->player)
        free(gen->player);

    if (gen->enemy)
    {
		for (int i = 0; i < 8; i++)
			free(gen->skeleton_enemy[i]);
        free(gen->enemy);
    }
}

void free_input_and_raycast(t_gen *gen)
{
    if (gen->rayhit)
        free(gen->rayhit);
    if (gen->kboard)
        free(gen->kboard);
    if (gen->mouse)
	{
        free(gen->mouse);
	}
	if (gen->door_texture)
		free(gen->door_texture);
	if (gen->door_texture2)
		free(gen->door_texture2);
	if (gen->flags)
		free(gen->flags);
}

void free_config_and_parsing(t_gen *gen)
{
    if (gen->def_values)
    {
        if (gen->def_values->env)
            ft_free_matrix(gen->def_values->env);

        if (gen->def_values->sounds.pids)
            free(gen->def_values->sounds.pids);

        free(gen->def_values);
    }
    if (gen->parse)
    {
        free_parsing(gen->parse);
        gen->parse = NULL;
    }
    if (gen->texture_data)
        free(gen->texture_data);
    if (gen->img_data)
	{
        free(gen->img_data);
	}
	if (gen->dda)
		free(gen->dda);
}

int super_duper_hiper_free(void)
{
    t_gen *gen = gen_stuff();

    stop_all_sounds(gen);

    free_images_and_textures(gen);
    free_game_objects(gen);
    free_input_and_raycast(gen);
    free_config_and_parsing(gen);
    if (gen->mlx_data)
    {
        if (gen->mlx_data->win_ptr)
            mlx_destroy_window(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr);

        if (gen->mlx_data->mlx_ptr)
        {
            mlx_destroy_display(gen->mlx_data->mlx_ptr);
            free(gen->mlx_data->mlx_ptr);
        }
        free(gen->mlx_data);
    }
    exit(0);
}
