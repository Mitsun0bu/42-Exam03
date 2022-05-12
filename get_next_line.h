#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define NO_NL -1

char	*get_next_line(int fd);
char	*get_line(int fd, char *line, char *buff);
int		ft_strlen(char *s);
int		ft_find_nl_index(char *s);
char	*ft_strjoin(char *line, char *buff);
