#include "./headers/cub3d.h"
#include "headers/mlx.h"

void	free_texture(void *mlx_ptr, t_texture *tex)
{
	if (!tex)
		return ;
	if (tex->img)
		mlx_destroy_image(mlx_ptr, tex->img); // free the MLX image
	free(tex);                                // free the struct
}

void	ft_free_matrix_partial(char **matrix, int max_index)
{
	int	i;

	if (!matrix)
		return ;
	for (i = 0; i < max_index; i++)
	{
		if (matrix && matrix[i])
			free(matrix[i]);
	}
	free(matrix);
}

void	ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	handle_exit(int keysys)
{
	if (keysys == XK_Escape)
		return (super_duper_hiper_free(), 1);
	return (0);
}

void	free_parsing(t_parsing *parse)
{
	int	i;

	i = 0;
	if (parse->textures_info)
	{
		while (i < E_COUNT)
		{
			free(parse->textures_info[i]);
			parse->textures_info[i] = NULL;
			i++;
		}
		free(parse->textures_info);
		parse->textures_info = NULL;
	}
	if (parse->map)
		free_double(parse->map);
	if (parse)
		free(parse);
}

int	super_duper_hiper_free(void)
{
	t_gen	*gen;

	gen = gen_stuff();
	stop_all_sounds(gen);
	if (gen->img_data->vignette)
		free(gen->img_data->vignette);
	if (gen->flags)
		free(gen->flags);
	if (gen->enemy_tex)
	{
		free_texture(gen->mlx_data->mlx_ptr, gen->enemy_tex);
		gen->enemy_tex = NULL;
	}

	if (gen->terror_arm)
	{
		if (gen->terror_arm->img)
			mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->terror_arm->img);
		free(gen->terror_arm);
	}
	if (gen->mlx_data)
	{
		if (gen->img_data->img)
			mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->img_data->img);
		if (gen->arm)
		{
			if (gen->arm->img)
				mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->arm->img);
			gen->arm->img = NULL;
			free(gen->arm);
		}
		for (int i = 0; i < 4; i++)
		{
			mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->texture[i]->img);
			free(gen->texture[i]);
		}
		if (gen->minimap->image.img)
			mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->minimap->image.img);
		if (gen->mlx_data->win_ptr)
			mlx_destroy_window(gen->mlx_data->mlx_ptr, gen->mlx_data->win_ptr);
		if (gen->mlx_data->mlx_ptr)
		{
			mlx_destroy_display(gen->mlx_data->mlx_ptr);
			gen->mlx_data->mlx_ptr = NULL; // prevents double-close
		}
		free(gen->mlx_data->mlx_ptr);
		free(gen->mlx_data);
		gen->mlx_data = NULL;
	}
	for (int i = 0; i < 4; i++)
		free(gen->terror_texture[i]);
	if (gen->def_values->env)
		ft_free_matrix(gen->def_values->env);
	if (gen->def_values->sounds.pids)
		free(gen->def_values->sounds.pids);
	if (gen->mouse)
		free(gen->mouse);
	if (gen->rayhit)
		free(gen->rayhit);
	if (gen->def_values)
		free(gen->def_values);
	if (gen->player)
		free(gen->player);
	if (gen->minimap)
	{
		if (gen->minimap->map)
			ft_free_matrix(gen->minimap->map);
		free(gen->minimap);
	}
	if (gen->enemy)
	{
		for (int i = 0; i < gen->enemy_count; i++)
			free(&gen->enemy[i]);
	}
	if (gen->kboard)
		free(gen->kboard);
	if (gen->texture_data)
		free(gen->texture_data);
	if (gen->img_data)
		free(gen->img_data);
	free_parsing(gen->parse);
	gen->parse = NULL;
	exit(0);
}
