/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfazzell <sfazzell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:37:25 by sfazzell          #+#    #+#             */
/*   Updated: 2024/04/25 14:38:10 by sfazzell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char	*stralloc(char *buf, int cut)
{
	static char	*str;
	char		*temp;

	if (!cut)
	{
		if (str)
			str = ft_strjoin(str, buf);
		else
			str = ft_strdup(buf);
		return (str);
	}
	else if (cut > 0)
	{
		if (str && str[cut])
		{
			temp = ft_strdup(str + cut);
			free(str);
			str = temp;
			return (NULL);
		}
		free(str);
	}
	else if (cut == -1 && str)
		free(str);
	return ((void)(str = NULL), NULL);
}

static char	*extracted_line(char *line, char *str, char *buf, int cut)
{
	free(buf);
	if (cut)
	{
		line = ft_substr(str, 0, ft_strchr(str, '\n') - str);
		stralloc(NULL, ft_strlen(line) + 1);
	}
	else
	{
		line = ft_strdup(str);
		stralloc(NULL, -1);
	}
	return (line);
}

static char	*last_line(char *str, char *line, char *buf)
{
	str = stralloc(buf, 0);
	if (str && ft_strchr(str, '\n'))
		return (extracted_line(line, str, buf, 1));
	else if (str && ft_strlen(str) > 0)
		return (extracted_line(line, str, buf, 0));
	else
		return ((void)stralloc(NULL, -1), free(buf), NULL);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*line;
	char		*buf;
	int			rd;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char) *(BUFFER_SIZE + 1));
	line = NULL;
	rd = 1;
	while(rd > 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		buf[rd] = '\0';
		str = stralloc(buf, 0);
		if (str && ft_strchr(str, '\n'))
				return (extracted_line(line, str, buf, 1));
	}
	if (rd == 0)
		return (last_line(str, line, buf));
	return (free(buf), NULL);
}
int main(int argc, char *argv[])
{
	int fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		printf("Failed to open file\n");
		return 1;
	}
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("line: %s\n", line);
		free(line);
	}
	close(fd);
	return 0;
}