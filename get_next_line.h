#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h> 
# include <stdlib.h> 

# define BUFFER_SIZE 42 

char    *get_next_line(int fd);
char	*ft_strcat(char *dest, char *src);
char    *ft_strcpy(char *s1, char *s2);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
size_t	ft_strlen(const char *s);

#endif
