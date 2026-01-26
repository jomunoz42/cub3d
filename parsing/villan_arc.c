// #include "../headers/cub3d.h"

// int is_valid_element_line(char *line)
// {
//     if (!line || !*line)
//         return (1); // empty line is allowed

//     if (!ft_strncmp(line, "NO ", 3)
//         || !ft_strncmp(line, "SO ", 3)
//         || !ft_strncmp(line, "WE ", 3)
//         || !ft_strncmp(line, "EA ", 3)
//         || !ft_strncmp(line, "F ", 2)
//         || !ft_strncmp(line, "C ", 2))
//         return (1);

//     return (0);
// }

// int is_map_line(char *line)
// {
//     int i = 0;

//     if (!line)
//         return (0);

//     while (line[i])
//     {
//         if (line[i] != '0' && line[i] != '1'
//             && line[i] != 'N' && line[i] != 'S'
//             && line[i] != 'E' && line[i] != 'W'
//             && line[i] != ' ' && line[i] != '\n')
//             return (0);
//         i++;
//     }
//     return (1);
// }


// int validate_file(int fd)
// {
//     char *line;
//     int map_started = 0;

//     while ((line = get_next_line(fd)))
//     {
//         if (!map_started)
//         {
//             if (line[0] == '\n')
//             {
//                 free(line);
//                 continue;
//             }

//             if (is_map_line(line))
//                 map_started = 1;
//             else if (!is_valid_element_line(line))
//             {
//                 free(line);
//                 return (printf("validate file didn't validate\n"), 0);
//             }
//         }
//         free(line);
//     }
// 	prinf("== look here: %d\n", map_started);
//     return (map_started); // map must exist
// }

