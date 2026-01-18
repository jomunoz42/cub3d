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
}	t_texture_data;

typedef struct s_general
{
	t_texture_data *texture_data;
	t_parsing	*parse;
	t_mlx_data	*mlx_data;
	void *arm;
}				t_gen;