#include "general.h"

typedef struct s_parsing
{
	char			**textures_info;
	const char		*error_messages[ERROR_COUNT];
	char			*file_path;
	char			**map;
	char			player;
	int				width;
	int				height;
	int				fd;
	int				seen_NO;
	int				seen_SO;
	int				seen_WE;
	int				seen_EA;
	int				seen_F;
	int				seen_C;
}					t_parsing;

typedef struct s_keyboard
{
	bool			key_w;
	bool			key_a;
	bool			key_s;
	bool			key_d;
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

typedef struct s_player
{
	double			x;
	double			y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;

}					t_player;

typedef struct s_images_data
{
	void			*img;
	char			*addr;
	int				bits_pixel;
	int				line_len;
	int				endian;
}					t_img_data;

typedef struct s_minimap
{
	t_img_data		image;
	char			**map;
	int				width;
	int				height;
}					t_minimap;

typedef struct s_general
{
	t_texture_data	*texture_data;
	t_parsing		*parse;
	t_mlx_data		*mlx_data;
	t_img_data		*img_data;
	t_player		*player;
	t_keyboard		*kboard;
	t_minimap		*minimap;
	void			*arm;
}					t_gen;
