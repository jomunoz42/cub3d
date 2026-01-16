#include "cub3d.h"

// t_parsing *parsing_init(void)
// {
//     t_parsing *new;

//     new = malloc(sizeof(t_parsing));
//     if (!new)
//         return (NULL);
//     new->textures_info = NULL;
//     new->error_messages = {
//         "Error: missing texture NO",
// 		"Error: missing texture SO",
// 		"Error: missing texture WE",
// 		"Error: missing texture EA",
// 		"Error: missing floor color",
// 		"Error: missing ceiling color"
// 	};
//     return (new);
// }

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
