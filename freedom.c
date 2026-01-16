#include "cub3d.h"

int super_duper_hiper_free(void)
{
    t_gen *gen = gen_stuff();

    if (gen->mlx_data)
    {
        if (gen->mlx_data->win_ptr)
            mlx_destroy_window(
                gen->mlx_data->mlx_ptr,
                gen->mlx_data->win_ptr
            );
        if (gen->mlx_data->mlx_ptr)
            mlx_destroy_display(gen->mlx_data->mlx_ptr);
		free(gen->mlx_data->mlx_ptr);
        free(gen->mlx_data);
        gen->mlx_data = NULL;
    }
    free_parsing(gen->parse);
    gen->parse = NULL;
    exit(0);
}

void ft_free_matrix(char **matrix)
{
	int i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int handle_exit(int keysys)
{
	if (keysys == XK_Escape)
		return (super_duper_hiper_free(), 1);
	return (0);
}

void free_parsing(t_parsing *parse)
{
    if (!parse)
        return;
    if (parse->textures_info)
		ft_free_matrix(parse->textures_info);
    free(parse);
}