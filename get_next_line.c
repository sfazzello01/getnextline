/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfazzell <sfazzell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:37:25 by sfazzell          #+#    #+#             */
/*   Updated: 2024/04/23 20:35:15 by sfazzell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char *get_next_line(int fd)
{
	char		*str;
	char		*line;
	char		*buf;
	int			rd;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buf = (char *)malloc(sizeof(char)*(BUFFER_SIZE + 1));
	rd = read(fd, buf, BUFFER_SIZE);
	buf[rd] = '\0'; // null-terminate the buffer
	while(rd > 0)
	{
		str = stralloc(buf, 0);
		if (str)
		{
			if (ft_strchr(str, '\n')) // check if newline character is present in str
			{
				line = extract_line(str, ft_strchr(str, '\n')); // extract the line from str
				free(buf);
				stralloc(NULL, ft_strlen(line) + 1);
				return line; // return the extracted line
			}
		}
		rd = read(fd, buf, BUFFER_SIZE); // read more characters from file into buffer
	}
	if (rd == 0) // reached end of file
	{
		str = stralloc(buf, 0);
		if (str)
		{
			if (ft_strchr(str, '\n'))
			{
				line = extract_line(str, ft_strchr(str, '\n'));
				free(str);
				free(buf);
				stralloc(NULL, ft_strlen(line) + 1);
				return (line); // return the extracted line
			}
			else if (ft_strlen(str) > 0)
			{
				line = ft_strdup(str);
				free(buf);
				stralloc(NULL, -1);
				return (line); // return the extracted line
			}
			stralloc(NULL, -1);
		}
		
		free(buf);
		return (NULL); // return NULL if no more lines to read
	}
	return (NULL); // return NULL in case of error
}
/*
int main (int argc, char **argv)
{
	int		fd;
	char	*line;

 	if (argc == 2)
 	{
 		fd = open(argv[1], O_RDONLY);
 		if (fd < 0)
 			return (0);
 		line = get_next_line(fd);
 		while (line)
 		{
 			//sleep(1);
 			printf("%s\n", line);
 			free(line);
 			line = get_next_line(fd);
 		}
 		close(fd);
 	}
 	return (0);
}*/