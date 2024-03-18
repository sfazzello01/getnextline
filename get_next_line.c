/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfazzell <sfazzell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:37:25 by sfazzell          #+#    #+#             */
/*   Updated: 2024/03/18 14:51:07 by sfazzell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *get_next_line(int fd)
{
	static char	*str;
	char		*line;
	char		*buf;
	int			rd;
	
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char)*(BUFFER_SIZE + 1));
	rd = read(fd, buf, BUFFER_SIZE);
	buf[rd] = '\0';
	while(rd > 0)
	{
		if (str == NULL)
			str = ft_strdup(buf);
		else
			str = ft_strjoin(str, buf);
		if (ft_strchr(str, '\n'))
		{
			line = ft_substr(str, 0, ft_strchr(str, '\n') - str);
			free(buf);
			str = ft_strdup(str + ft_strlen(line) + 1);
			return line;
		}
		rd = read(fd, buf, BUFFER_SIZE);
		buf[rd] = '\0';
	}
	if (rd == 0)
	{
		if (str == NULL)
		{
			free(buf);
			return (NULL);
		}
		if (ft_strchr(str, '\n'))
		{
			line = ft_substr(str, 0, ft_strchr(str, '\n') - str);
			str = ft_strdup(str + ft_strlen(line) + 1);
			free(buf);
			return (line);
		}
		line = ft_strdup(str);
		free(buf);
		str = NULL;
		return (line);
	}
	return (NULL);
}

int main (int argc, char **argv)
{
	int fd;
	char *line;
	if (argv){}

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		//fd = 1;
		if (fd < 0)
			return (0);
		line = get_next_line(fd);
		while (line)
		{
			printf("%s\n", line);
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (0);
}