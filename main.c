#include "cub3d.h"
#include <fcntl.h>

void free_parsing(t_parsing *parse)
{
    if (!parse)
        return;
    if (parse->textures_info)
		ft_free_matrix(parse->textures_info);
    free(parse);
}

int main(int argc, char *argv[])
{
    t_gen *gen;

    gen = gen_stuff();

    if (initial_parsing(argc, argv) != 0)
        return (1);

    gen->parse = parsing_init();
    if (!gen->parse)
        return (printf("Error: error initializing parsing\n"), 1);

    if (!validate_textures_path(argv[1], gen->parse))
        return (super_duper_hiper_free(), 1);

    printf("\n==All right from here==\n");

    start_window();

    return (0);
}


// int main(int argc, char *argv[])
// {
// 	t_parsing *parsing;
//     if (initial_parsing(argc, argv) != 0)
// 		return (1);
// 	parsing = parsing_init();
// 	if (!parsing)
// 		return (printf("Error: error initializing parsing\n"), 1);
// 	if (validate_textures_path(argv[1], parsing) == 0)
// 		return (free(parsing), 1);
// 	printf("\n==All right from here==\n");
// 	start_window();
// 	printf("STILL TESTING FROM HERE: %s", parsing->textures_info[3]);
// 	free_parsing(parsing);
// 	super_duper_hiper_free();
// 	return (0);
// }
