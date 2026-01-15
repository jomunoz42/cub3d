
#ifndef CUB3D_H
# define CUB3D_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include <errno.h>
#define prinf printf

int ft_strcmp(char *s1, char *s2);



int     map_parser(char *argv);

char    *get_next_line(int fd);

int	    ft_strncmp(const char *s1, const char *s2, size_t n);
int 	ft_strlen(const char *s);

#endif
