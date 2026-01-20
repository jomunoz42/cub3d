#include "general.h"

typedef struct s_parsing
{
	char		**textures_info;
	const char	*error_messages[ERROR_COUNT];
	int 		fd;
}				t_parsing;

typedef struct s_mlx_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			window_width;
	int			window_height;
}				t_mlx_data;

typedef struct texture_data
{
	uint32_t	arm_width;
	uint32_t	arm_height;
	int			horizon;
	int			flr_color;
	int			clng_color;
}	t_texture_data;

// typedef struct s_minimap this wil draw the shit twice
// {
// 	char **map;
// 	void *img;
// 	char *addr;
// 	int bits_per_pixel;
// 	int line_len;
// 	int endian;
// }	t_minimap;

typedef struct s_player
{
	int	x;
	int y;
	
}	t_player;

typedef struct s_images_data
{
	void	*img;
	char *addr;
	int bits_per_pixel;
	int line_len;
	int endian;
}	t_img_data;

typedef struct s_general
{
	t_texture_data *texture_data;
	t_parsing	*parse;
	t_mlx_data	*mlx_data;
	t_img_data *img_data;
	t_player 	*player;
	// t_minimap *minimap;
	void *arm;
}				t_gen;