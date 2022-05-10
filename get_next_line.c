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

char	*get_next_line(int fd)
{
	char		*line = NULL;
	static char	buff[BUFFER_SIZE + 1] = {};

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = malloc(sizeof(char) * 1);
	if (!line)
		return (NULL);
	line[0] = 0;
	line = get_line(fd, line, buff);
	if (line && ft_strlen(line))
		return (line);
	free(line);
	return (NULL);
}

char	*get_line(int fd, char *line, char *buff)
{
	char	*buff_rest = NULL;
	int		read_ret = 1;

	while (read_ret > 0)
	{
		line = ft_strjoin(line, buff);
		if (!line)
			return (NULL);
		if (ft_find_nl_index(buff) != NO_NL)
		{
			buff_rest = &buff[ft_find_nl_index(buff) + 1];
			while (*buff_rest)
				*buff++ = *buff_rest++;
			*buff = '\0';
			return (line);
		}
		read_ret = read(fd, buff, BUFFER_SIZE);
		if (read_ret == -1)
		{
			free(line);
			return (NULL);
		}
		buff[read_ret] = '\0';
	}
	return (line);
}

int	ft_strlen(char *s)
{
	int	i = 0;

	if (!s)
		return (i);
	while (s[i])
		i ++;
	return (i);
}

int	ft_find_nl_index(char *s)
{
	int	i = 0;

	if (!s)
		return (NO_NL);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i ++;
	}
	return (NO_NL);
}

char	*ft_strjoin(char *line, char *buff)
{
	char	*joined = NULL;
	int		buff_size = 0;
	int		i_l = 0;
	int		i_b = 0;

	if (ft_find_nl_index(buff) == NO_NL)
		buff_size = ft_strlen(buff);
	else
		buff_size = ft_find_nl_index(buff);
	joined = malloc(sizeof(char) * (ft_strlen(line) + buff_size + 1));
	if (!joined)
		return (NULL);
	i_l = -1;
	while (line[++i_l])
		joined[i_l] = line[i_l];
	free(line);
	i_b = -1;
	while (buff[++i_b])
	{
		joined[i_l] = buff[i_b];
		if (buff[i_b] == '\n')
			break ;
		i_l ++;
	}
	joined[i_l] = '\0';
	return (joined);
}

