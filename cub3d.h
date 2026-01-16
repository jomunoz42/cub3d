
#ifndef CUB3D_H
# define CUB3D_H

# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <X11/keysym.h>
# include <X11/X.h>
#include "mlx.h"
# define ERROR_COUNT 12
# define prinf printf

typedef struct s_parsing
{
	char		**textures_info;
	const char	*error_messages[ERROR_COUNT];
}				t_parsing;

t_parsing		*parsing_init(void);
int				ft_strcmp(char *s1, char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_strcpy(char *s1, char *s2);
void			ft_print_matrix(char **matrix);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *nptr);
int				struct_sharingan(char *file, t_parsing *parse);
int				initial_parsing(int argc, char *argv[]);
int				ft_matrix_len(char **matrix);
int				validate_textures_path(char *argv, t_parsing *parse);
int start_window(void);

int				map_parser(char *argv);

char			*get_next_line(int fd);

int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strlen(const char *s);

#endif
