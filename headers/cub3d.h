
#ifndef CUB3D_H
# define CUB3D_H

# include "general.h"
# include "typedef.h"

int			ft_strcmp(char *s1, char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strtrim(char const *s1, char const *set);
char		*ft_strcpy(char *s1, char *s2);
void		ft_print_matrix(char **matrix);
int			ft_matrix_len(char **matrix);
int			ultimate_file_validation(char *argv, t_parsing *parse);
int			init_all(t_gen *gen);
void		ft_free_matrix(char **matrix);
int			super_duper_hiper_free(void);
void		file_closer(void);
void		free_parsing(t_parsing *parse);
int	window_init(t_gen *gen, int w, int h);
int			handle_exit(int keysys);
void		ft_free_matrix_partial(char **matrix, int max_index);
int			png_size_fd(const char *path, uint32_t *w, uint32_t *h);
int			png_size_fd(const char *path, uint32_t *w, uint32_t *h);
int			rgb_to_hex(int r, int g, int b);
int			color_switch(char *str);
char		*space_skipper_shift(char *str);
int game_loop(t_gen *gen);
void		copied_mlx_pixel_put(t_img_data *img_data, int x, int y, int color);
int			only_num(char *str);
int			validate_file(int fd);
char		**refactored_shit(char *file);
int			validate_file(int fd);
void draw_static_minimap(t_gen *gen);
int is_wall(t_gen *gen, int map_x, int map_y);
int			get_player_position(t_gen *gen);
void direction_hits_wall(t_gen *gen, double ray_direction_x, double ray_direction_y);
void		draw_minimap(t_gen *gen);
int			move_player(int keysym, t_gen *gen);
void		ft_bzero(void *s, size_t n);
void	genesis(t_gen *gen);
void draw_arm(t_gen *gen);
void		draw_minimap_tile(t_gen *gen, int row, int col, int color);
int			key_press(int key, t_gen *gen);
int			key_release(int key, t_gen *gen);
bool collision(t_gen *gen, double next_y, double next_x);
void render_scene(t_gen *gen);
void		draw_minimap(t_gen *gen);
int			key_handler(int keysym, t_gen *gen);
void		draw_minimap_tile(t_gen *gen, int row, int col, int color);
int	ft_abs(int n);
int main_loop(t_gen *gen);
int			key_press(int key, t_gen *gen);
int			key_release(int key, t_gen *gen);
t_gen		*gen_stuff(void);
t_parsing	*parsing_init(void);
int main_init(t_gen *gen, char *argv, char **environ);
int	start_window(t_gen *gen, char *argv);
void render_scene(t_gen *gen);
void draw_minimap_fov(t_gen *gen);
int get_pixel_color(t_gen *gen, int x, int y);
int get_pixel_color_img(t_img_data *img, int x, int y);
void init_vignette(t_img_data *img);
void ciclope_dos_xman(t_img_data *img,int x0, int y0, int x1, int y1, int color);
int png_name_to_xpm(t_gen *gen, char *xpm_files[4]);
void rotate_player(t_gen *gen, double angle);
int mouse_looking(t_gen *gen);
t_rayhit castrate(t_gen *gen, double ray_direction_x, double ray_direction_y, bool interact);
void draw_terror_arm(t_gen *gen);
int apply_fog(int color, double dist);
void play_music(t_gen *gen);
void start_terror_music(t_gen *gen);
void stop_all_sounds(t_gen *gen);
void play_sound(t_gen *gen, const char *filename, int loop);
int	apply_fog(int color, double dist);
void open_close_door(t_gen *gen);
t_texture *load_xpm_texture(void *mlx_ptr, char *file);


//====================== ENEMY =========================

void        update_enemy_animation(t_enemy *enemy, int i);
void        find_enemy_from_map(t_gen *gen, int i);
void        update_enemy(t_gen *gen, int i);
void        draw_enemy(t_gen *gen, int i);
void        draw_enemy_minimap(t_gen *gen);
int         count_enemies_in_map(t_gen *gen);
bool        enemy_visible(t_gen *gen, double *distance_out, int i);

//===================== PARSING ========================

int	        parser(t_gen *gen, int argc, char **argv);
int	        is_map_valid(t_parsing *data);
int	        construct_map_and_textures(t_parsing *data);
int			not_last_element(t_parsing *data);
int			is_header_line(t_parsing *data, char *line);
int         check_all_elements(t_parsing *data, char *line);
int	        is_rgb_colours_invalid(t_parsing *data, char *line, char c, int type);
int         is_header_line_with_validation(t_parsing *data, char *line);

//====================== UTILS =========================

char		*get_next_line(int fd);
int         contains_tab(char *s);
int			is_line_empty(char *line);
void		free_double(char **arg);
int         ft_clamp(int value, int min, int max);

//====================== LIBFT =========================

char	    *ft_strchr(const char *s, int c);
int     	ft_isdigit(int c);
char	    *ft_strdup(const char *s);
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
char        *ft_strncpy(char *dst, char *srce, int n);
char        *ft_strcat(char *dst, char *srce);
char	    *ft_itoa(int n);
char	    *ft_strjoin(char *s1, char *s2);
void	    ft_putstr_fd(char *s, int fd);

#endif