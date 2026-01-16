
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
#define prinf printf

typedef struct s_parsing{
    char **textures_info;
}   t_parsing;

t_parsing *parsing_init(void);
int ft_strcmp(char *s1, char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strtrim(char const *s1, char const *set);
char    *ft_strcpy(char *s1, char *s2);
void	ft_print_matrix(char **matrix);
char	**ft_split(char const *s, char c);
int	ft_atoi(const char *nptr);
void get_texture_info(char *file, t_parsing *parse);
int parse(int argc, char *argv[]);
int ft_matrix_len(char **matrix);


int     map_parser(char *argv);

char    *get_next_line(int fd);

int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int 	ft_strlen(const char *s);

#endif
