#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "../cub3d.h"
# define BUFFER_SIZE 2

int ft_strlen(const char *str)
{
    size_t i = 0;
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

char *ft_strchr(char *str, int c)
{
    int i = 0;
    if (!str)
        return (NULL);
    if (c == '\0')
        return ((char *)str + ft_strlen(str));
    while (str[i])
    {
        if (str[i] == c)
            return ((char *)str + i);
        i++;
    }
    return (NULL);
}

char *ft_strjoin(char *s1, char *s2)
{
    char *joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!joined)
        return (NULL);
    int i = 0, j = 0;
    if (s1)
    {
        while (s1[i] != '\0')
        {
            joined[i] = s1[i];
            i++;
        }
    }
    while (s2[j] != '\0')
    {
        joined[i + j] = s2[j];
        j++;
    }
    joined[i + j] = '\0';
    free(s1);
    return (joined);
}

char *full_line(char *full_line, char *file_str)
{
    int i = 0, j = 0;
    while (file_str[i] != '\0' && file_str[i] != '\n')
        i++;
    if (file_str[i] == '\n')
        i++;
    char *temp = malloc(i + 1);
    if (!temp)
        return (NULL);
    while (j < i)
    {
        temp[j] = file_str[j];
        j++;
    }
    temp[j] = '\0';
    j = 0;
    while (file_str[i] != '\0')
        file_str[j++] = file_str[i++];
    file_str[j] = '\0';
    full_line = ft_strjoin(full_line, temp);
    free(temp);
    return (full_line);
}

char *get_next_line(int fd)
{
    static char file_str[BUFFER_SIZE + 1];
    char *print = NULL;
    int count;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    while (1)
    {
        if (file_str[0] == '\0')
        {
            count = read(fd, file_str, BUFFER_SIZE);
            if (count <= 0)
                break ;
            file_str[count] = '\0';
        }
        if (ft_strchr(file_str, '\n'))
            return (full_line(print, file_str));
        print = ft_strjoin(print, file_str);
        file_str[0] = '\0';
    }
    if (count < 0)
        return (free(print), NULL);
    return (print);
}
