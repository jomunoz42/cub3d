
#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <errno.h>

typedef struct s_parsing
{
    char    *file_path;
    char    **textures_info;
    char    **map;
    int     width;
    int     height;
}              t_parsing;

//===================== PARSING ========================

int     ft_floodfill(char **map, int y, int x);
int     map_parser(t_parsing *parser, char *argv);
int	    find_no_player(t_parsing *data);
int	    find_multiple_player(t_parsing *data);
int     find_invalid_char(t_parsing *data);

//====================== UTILS =========================

char    *get_next_line(int fd);

void	free_double(char **arg);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t  ft_strlen(char *str);

#endif
