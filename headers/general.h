#ifndef GENERAL_H
# define GENERAL_H
# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define prinf printf
# define ERROR_COUNT 12
# define WIN_WIDTH 1200
# define WIN_HEIGHT 1000
# define FLOOR_COLOR "150,86,30"
# define CEILING_COLOR "14,226,249"
# define MINIMAP_SCALE 15
# define MOVE_SPEED 0.009
#define ROTATION_SPEED 0.009

# define USER_HAND_XPM "./imgs/arm_placeholder.xpm"
# define USER_HAND_PNG "./imgs/arm_placeholder.png"

#endif