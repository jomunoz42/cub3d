
#include "../headers/cub3d.h"

static char  *skip_new_lines(char *line, int fd)
{
    while (!ft_strncmp(line, "\n", 1))
    {
        free(line);
        line = get_next_line(fd);
    }
    return (line);
}

static int skip_and_count(char *argv)
{
    char *line;
    int  size;
    int  fd;
    
    size = 0;
    fd = open(argv, O_RDONLY);
    line = get_next_line(fd);
    line = skip_new_lines(line, fd);
    while(line)
    {
        size++;
        free(line);
        line = get_next_line(fd);
    }
    return (size);
}

static char  **map_allocation(char *argv)
{
    char **map;
    char *line;
    int  size;
    int  fd;
    int  i;

    i = -1;
    fd = open(argv, O_RDONLY);
    size = skip_and_count(argv);
    map = malloc(sizeof(char *) * (size + 1));
    if (!map)
        (write(2, "Error: Allocation failed.", 25), exit(1));
    while(++i < size)
    {
        line = get_next_line(fd);
        line = skip_new_lines(line, fd);
        map[i] = malloc(sizeof(char) * (ft_strlen(line) + 1));
        if (!map[i])
            (write(2, "Error: Allocation failed.", 25), exit(1));
        ft_memcpy(map[i], line, ft_strlen(line));
    }
    map[i] = NULL;
    return (map);
}

int map_parser(char *argv)
{
    char **map;
    int i = 0;

    map = map_allocation(argv);
    while (map[i])
    {
        printf("%s", map[i]);
        i++;
    }
    return (0);
}


//     Precisa saltar as textures e as cores

//     Skip_new_lines incompleto, so pode saltar das cores ao mapa  (junta varios mapas)


//     Implementar floodfill em tudo o que e mapa (nao 1) que esta adjacente em espaco