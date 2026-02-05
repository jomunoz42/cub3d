#include "general.h"

typedef enum e_element
{
    E_NO = 0,
    E_SO,
    E_WE,
    E_EA,
    E_F,
    E_C,
    E_COUNT
} t_element;

typedef struct s_mouse
{
	int	previous_x;
	int	x;
	int y;
	double	sens;
}	t_mouse;

typedef struct s_parsing
{
	char 			**textures_info;
	char			**map;
	char			player;
	int				width;
	int				height;
	int				fd;
	int     		elements[E_COUNT];
}					t_parsing;

typedef struct s_keyboard
{
	bool			key_w;
	bool			key_a;
	bool			key_s;
	bool			key_d;
	bool			key_right;
	bool			key_left;
	bool			control_left;
	bool			shift_left;
	bool			key_f;
	bool			key_l;
}					t_keyboard;

typedef struct s_mlx_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_width;
	int				win_height;
}					t_mlx_data;

typedef struct texture_data
{
	uint32_t		arm_width;
	uint32_t		arm_height;
	int				horizon;
	int				flr_color;
	int				clng_color;
}					t_texture_data;

typedef struct s_texture
{
	void *img;
	int *data;
	int width;
	int height;
}	t_texture;

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
	double			rotate_speed;
	double			fov;
}					t_player;

typedef struct s_images_data
{
    void *img;
    char *addr;
    int bits_pixel;
    int line_len;
    int endian;
    int width;
    int height;
	float	*vignette;
} t_img_data;


typedef struct s_minimap
{
	t_img_data		image;
	char			**map;
	int				width;
	int				height;
}					t_minimap;

typedef enum e_wall_face {
    NORTH,
    SOUTH,
    EAST,
    WEST
} t_wall_face;

typedef struct s_rayhit
{
    int     map_x;
    int     map_y;
    int     side;
    double  dist;
	t_wall_face face;
}   t_rayhit;


typedef struct s_general
{
	t_texture_data	*texture_data;
	t_parsing		*parse;
	t_mlx_data		*mlx_data;
	t_img_data		*img_data;
	t_player		*player;
	t_keyboard		*kboard;
	t_minimap		*minimap;
	t_rayhit		*rayhit;
	t_img_data			*arm;
	t_texture		*texture[4];
	t_mouse			*mouse;
}					t_gen;
