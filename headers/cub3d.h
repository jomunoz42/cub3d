
#ifndef CUB3D_H
# define CUB3D_H

# include "general.h"
#include "typedef.h"

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
int				start_window(void);
int				mlx_data_init(void);
t_gen			*gen_stuff(void);
void			ft_free_matrix(char **matrix);
int				super_duper_hiper_free(void);
void			file_closer(void);
void			free_parsing(t_parsing *parse);
int				handle_exit(int keysys);
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_free_matrix_partial(char **matrix, int max_index);
int png_size_fd(const char *path, uint32_t *w, uint32_t *h);
int png_size_fd(const char *path, uint32_t *w, uint32_t *h);
int rgb_to_hex(int r, int g, int b);
int color_switch(char *str);

int				map_parser(char *argv);

char			*get_next_line(int fd);

int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strlen(const char *s);

#endif
