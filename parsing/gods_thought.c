#include "../headers/cub3d.h"

typedef enum e_parse_state
{
    PARSE_HEADER,
    PARSE_MAP,
    PARSE_DONE
}   t_parse_state;


int is_empty_line(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\n' && line[i] != '\t')
            return (0);
        i++;
    }
    return (1);
}

int is_map_line(char *line)
{
    int i = 0;

    while (line[i] && line[i] != '\n')
    {
        if (line[i] != '0' && line[i] != '1'
            && line[i] != 'N' && line[i] != 'S'
            && line[i] != 'E' && line[i] != 'W'
            && line[i] != ' ')
            return (0);
        i++;
    }
    return (1);
}


int is_texture_or_color(char *line)
{
    if (!ft_strncmp(line, "NO ", 3)) return (1);
    if (!ft_strncmp(line, "SO ", 3)) return (1);
    if (!ft_strncmp(line, "WE ", 3)) return (1);
    if (!ft_strncmp(line, "EA ", 3)) return (1);
    if (!ft_strncmp(line, "F ", 2))  return (1);
    if (!ft_strncmp(line, "C ", 2))  return (1);
    return (0);
}

int enlightment(char *file)
{
    int             fd;
    char            *line;
    t_parse_state   state;

    state = PARSE_HEADER;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (printf("Error: cannot open file\n"), 0);
    while ((line = get_next_line(fd)))
    {
        if (state == PARSE_HEADER)
        {
            if (is_empty_line(line))
                ; // allowed
            else if (is_texture_or_color(line))
                ; // allowed (you already parse these elsewhere)
            else if (is_map_line(line))
                state = PARSE_MAP;
            else
                return (free(line), close(fd), printf("Error: invalid line before map\n"), 0);
        }
        else if (state == PARSE_MAP)
        {
            if (is_map_line(line))
                ; // allowed
            else if (is_empty_line(line))
                state = PARSE_DONE;
            else
                return (free(line), close(fd), printf("Error: invalid line inside map\n"), 0);
        }
        else if (state == PARSE_DONE)
        {
            if (!is_empty_line(line))
                return (free(line), close(fd), printf("Error: content after map\n"), 0);
        }
        free(line);
    }
    close(fd);
    if (state != PARSE_MAP && state != PARSE_DONE)
        return (printf("Error: map not found\n"), 0);

    return (1);
}
