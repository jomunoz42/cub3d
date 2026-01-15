#include "cub3d.h"

int validate_textures(char *file, char *one_direction) //remember to check access depois
{
	char *file_str, final_str;
	int cube_file_fd = open(file, O_RDONLY);
	if (cube_file_fd == -1)
		return (printf("Read nao fucionou\n"), 0);
	while (1)
	{
		read(cube_file_fd, file_str, 2);
		if ( ft_strcmp(file_str, "NO") == 1 || ft_strcmp(file_str, "SO")  == 1|| ft_strcmp(file_str, "WE") == 1 || ft_strcmp(file_str, "EA") == 1) //maybe use strcmp?
		{
			printf("achou\n");
			break ;
		}
		prinf("String = [%s]\n", file_str);
		printf("ainda nao\n");
	}
	return (1);
}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (printf("arguments\n"), 1);
	if (validate_textures(argv[1], "NO") == 0)
		return (printf("Deu bo no validate texture\n"), 0);
	return (0);
}

// NO
// SO
// WE 
// EA 