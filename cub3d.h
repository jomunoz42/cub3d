
#ifndef CUB3D
# define CUB3D

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <errno.h>

int     map_parser(char *argv);

char    *get_next_line(int fd);

int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int 	ft_strlen(const char *s);

#endif
