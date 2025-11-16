#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H


#ifndef BUFFER_SIZE
#define BUFFER_SIZE 69
#endif



#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strndup(const char *src, size_t n);
ssize_t	ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);
#endif