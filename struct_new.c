#include "cub3d.h"
#include "mlx.h"

t_parsing *parsing_init(void)
{
    t_parsing *new;

    new = malloc(sizeof(t_parsing));
    if (!new)
        return NULL;

    *new = (t_parsing){ //check and study this later
        .textures_info = NULL,
        .error_messages = {
            "Error: missing north texture [NO]",
            "Error: missing south texture [SO]",
            "Error: missing west texture [WE]",
            "Error: missing east texture [EA]",
            "Error: missing floor color [F]",
            "Error: missing ceiling color [C]",
            "Error: can't find north texture file",
            "Error: can't find south texture file",
            "Error: can't find west texture file",
            "Error: can't find east texture file",
            "Error: floor color invalid",
            "Error: ceiling color invalid"
        }
    };
    return new;
}

int mlx_data_init(void)
{
    t_gen *gen;

    gen = gen_stuff();
    gen->mlx_data = malloc(sizeof(t_mlx_data));
    if (!gen->mlx_data)
        return (1);

    gen->mlx_data->mlx_ptr = mlx_init();
    if (!gen->mlx_data->mlx_ptr)
        return (1);
    gen->mlx_data->win_ptr = NULL;
    return (0);
}
