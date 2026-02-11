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
	bool			tab;
	bool			key_right;
	bool			key_left;
	bool			control_left;
	bool			shift_left;
	bool			key_f;
	bool			key_l;
	bool			key_t;
	bool			key_i;
	bool			key_z;
	bool			key_x;
	bool			key_m;
	bool			key_caps_lock;
	bool			key_e;
	bool			key_num_one;
	bool			key_num_two;
	bool			key_num_three;
	bool			key_num_four;
	bool			key_num_five;
	bool			key_num_six;

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
	uint32_t		terror_arm_width;
	uint32_t		terror_arm_height;
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
	double				zoom_level;
}					t_minimap;

typedef enum e_wall_face {
    NORTH,
    SOUTH,
    EAST,
    WEST
} t_wall_face;

typedef enum e_hit_type 
{
    HIT_WALL,
    HIT_DOOR
} t_hit_type;

typedef struct s_rayhit
{
    int     map_x;
    int     map_y;
    int     side;
    double  dist;
	double zbuffer[WIN_WIDTH];
	t_wall_face face;
	t_hit_type  type;
}   t_rayhit;

typedef struct s_flags
{
	bool terror_mode;
	bool info;
	bool minimap;
	bool enemy_mini;
	bool mouse_on;
	bool music_on;
}	t_flags;

typedef struct s_sound
{
    pid_t *pids;
    int count;
    int capacity;
	pid_t terror_music_pid;
} t_sound;

typedef struct s_default_values
{
	double player_x;
	double player_y;
	double player_move_speed;
	double player_rotation_speed;
	double minimap_zoom_level;
	double fov;
	double terror_player_move_speed;
	char **env;
	t_sound sounds;
}	t_def_values;

typedef enum e_enemy_type
{
    ENEMY_GHOST,
    ENEMY_CTHULHU,
    ENEMY_SKELETON
} t_enemy_type;

typedef struct s_enemy
{
	double 			x;
	double 			y;
	double 			move_speed;
	int 			size;
	int    			enemy_frame;
    int   			enemy_timer;
	t_enemy_type    type;
}	t_enemy;

typedef struct s_node
{
    int x;
    int y;
} t_node;

typedef struct s_general
{
	t_flags			*flags;
	t_texture_data	*texture_data;
	t_parsing		*parse;
	t_mlx_data		*mlx_data;
	t_img_data		*img_data;
	t_player		*player;
	t_keyboard		*kboard;
	t_minimap		*minimap;
	t_rayhit		*rayhit;
	t_img_data		*arm;
	t_img_data		*terror_arm;
	t_texture		*texture[4];
	t_texture		*terror_texture[4];
	t_texture		*ghost_enemy[4];
	t_texture		*cthulhu_enemy[2];
	t_texture		*skeleton_enemy[7];
	t_texture		*enemy_tex;
	t_texture		*door_texture;
	t_texture		*door_texture2;
	t_mouse			*mouse;
	t_def_values	*def_values;
	t_enemy			*enemy;
	int				enemy_count;
}					t_gen;
