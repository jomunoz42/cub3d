#include "./headers/cub3d.h"

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
	int i;

	i = 0;
	if (parse->fd > 2)
	{
		close(parse->fd);
		parse->fd = -1;
	}
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
	if (gen->mlx_data)
	{
		if (gen->img_data->img)
			mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->img_data->img);
		if (gen->arm)
		{
			if (gen->arm->img)
				mlx_destroy_image(gen->mlx_data->mlx_ptr, gen->arm->img);
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
			mlx_destroy_display(gen->mlx_data->mlx_ptr);
		free(gen->mlx_data->mlx_ptr);
		free(gen->mlx_data);
		gen->mlx_data = NULL;
	}
	if (gen->mouse)
		free(gen->mouse);
	if (gen->rayhit)
		free(gen->rayhit);
	if (gen->player)
		free(gen->player);
	if (gen->minimap)
	{
		if (gen->minimap->map)
			ft_free_matrix(gen->minimap->map);
		free(gen->minimap);
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
