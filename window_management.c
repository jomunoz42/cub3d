#include "cub3d.h"

int handle_exit(int keysys)
{
	printf("handling\n");
	if (keysys == XK_Escape)
		exit(0) ;
	return (0);
}

int start_window(void)
{
	void* mlx_ptr;
	void *win_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (1);
	win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "salve");
	if (!win_ptr)
		return (printf("ANIMAL DO KRL\n"), 1);
	printf("before\n");
	mlx_loop_hook(mlx_ptr, handle_exit, NULL);
	mlx_loop(mlx_ptr); //eventually create a loop function
	mlx_destroy_window(mlx_ptr, win_ptr);
	return (0);
}