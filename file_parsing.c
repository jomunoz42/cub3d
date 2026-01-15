#include "cub3d.h"
#include <fcntl.h>

char *validate_texture_path(char *file, char *one_direction)
{
	int fd;
	char *line;
	char *path;
	int len;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error when opening the file\n"), NULL);
	len = ft_strlen(one_direction);
	while ((line = get_next_line(fd)))
	{
		if (ft_strncmp(line, one_direction, len) == 0 && line[len] == ' ')
		{
			path = ft_strtrim(line + len + 1, "\n");
			free(line);
			close(fd);
			return (path);
		}
		free(line);
	}
	close(fd);
	return (NULL);
}


char **texture_info(char *file)
{
	char *north_texture = validate_texture_path(file, "NO");
	char *south_texture = validate_texture_path(file, "SO");
	char *west_texture = validate_texture_path(file, "WE");
	char *east_texture = validate_texture_path(file, "EA");
	char *floor_color = validate_texture_path(file, "F");
	char *ceiling_color = validate_texture_path(file, "C");
	if (!north_texture || !south_texture || !west_texture ||
		!east_texture || !floor_color || !ceiling_color)
	{
		printf("Error: missing texture or color\n");
		return NULL;
	}

	int size = ft_strlen(north_texture) + 
				ft_strlen(south_texture) + ft_strlen(west_texture) + 
				ft_strlen(east_texture) + ft_strlen(floor_color) + ft_strlen(ceiling_color);

	char **final_info = malloc(sizeof(char *) * 7);

	if (!final_info)
		return (NULL);

	final_info[0] = malloc(ft_strlen(north_texture) + 1);
	final_info[1] = malloc(ft_strlen(south_texture) + 1);
	final_info[2] = malloc(ft_strlen(west_texture) + 1);
	final_info[3] = malloc(ft_strlen(east_texture) + 1);
	final_info[4] = malloc(ft_strlen(floor_color) + 1);
	final_info[5] = malloc(ft_strlen(ceiling_color) + 1);
	final_info[6] = NULL;
	ft_strcpy(final_info[0], north_texture);
	ft_strcpy(final_info[1], south_texture);
	ft_strcpy(final_info[2], west_texture);
	ft_strcpy(final_info[3], east_texture);
	ft_strcpy(final_info[4], floor_color);
	ft_strcpy(final_info[5], ceiling_color);

	ft_print_matrix(final_info);
	return (final_info);

	

}

int main(int argc, char *argv[])
{
	if (argc != 2)
		return (printf("arguments\n"), 1);
	texture_info(argv[1]);
	return (0);
}

// NO
// SO
// WE 
// EA 