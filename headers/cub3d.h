
#ifndef CUB3D_H
# define CUB3D_H

# include "general.h"
# include "typedef.h"

void		ft_print_matrix(char **matrix);
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
char		**refactored_shit(char *file);

// JHONNY STUFF

//===================== PARSING ========================

int	        parser(t_gen *gen, int argc, char **argv);
int			construct_map(t_parsing *data);
int         is_map_valid(t_parsing *data);
int         is_header_line_with_validation(t_parsing *data, char *line);
int         check_all_elements(t_parsing *data);
int     	is_rgb_colours_invalid(char *line, char c);
t_parsing	*parsing_init(void);

//====================== UTILS =========================

char		*get_next_line(int fd);
int         contains_tab(char *s);
int			is_line_empty(char *line);
void		free_double(char **arg);

//====================== LIBFT =========================

char	    *ft_strchr(const char *s, int c);
int     	ft_isdigit(int c);
char	    *ft_strrchr(const char *s, int c);
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
