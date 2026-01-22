
#ifndef CUB3D_H
# define CUB3D_H

# include "general.h"
# include "typedef.h"

t_parsing	*parsing_init(void);
void		ft_print_matrix(char **matrix);
int			struct_sharingan(char *file, t_parsing *parse);
int			ft_matrix_len(char **matrix);
int			ultimate_file_validation(char *argv, t_parsing *parse);
int			start_window(void);
int			mlx_data_init(void);
t_gen		*gen_stuff(void);
void		ft_free_matrix(char **matrix);
int			super_duper_hiper_free(void);
void		file_closer(void);
void		free_parsing(t_parsing *parse);
int			handle_exit(int keysys);
void		ft_free_matrix_partial(char **matrix, int max_index);
int			png_size_fd(const char *path, uint32_t *w, uint32_t *h);
int			png_size_fd(const char *path, uint32_t *w, uint32_t *h);
int			rgb_to_hex(int r, int g, int b);
int			color_switch(char *str);
char		*space_skipper_shift(char *str);
void		copied_mlx_pixel_put(t_img_data *img_data, int x, int y, int color);
int			only_num(char *str);
int			validate_file(int fd);
char		**refactored_shit(char *file);
int			validate_file(int fd);

// JHONNY STUFF

//===================== PARSING ========================

int	        parser(t_gen *gen, int argc, char **argv);
int         initial_parsing(int argc, char *file_path);
int			construct_map(t_parsing *data);
int			find_no_player(t_parsing *data);
int			find_multiple_player(t_parsing *data);
int			find_invalid_char(t_parsing *data);
int			is_line_empty(char *line);

//====================== UTILS =========================

char		*get_next_line(int fd);

void		free_double(char **arg);

//====================== LIBFT =========================

void		ft_bzero(void *s, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
int			ft_strlen(const char *str);
int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strcpy(char *s1, char *s2);
void		*ft_calloc(size_t nmemb, size_t size);
char		**ft_split(char const *s, char c);
int			ft_atoi(const char *nptr);

#endif
