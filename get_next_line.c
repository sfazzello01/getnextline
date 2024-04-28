/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfazzell <sfazzell@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:37:25 by sfazzell          #+#    #+#             */
/*   Updated: 2024/04/28 15:04:00 by sfazzell         ###   ########.fr       */
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
		// If str is not NULL, concatenate it with buf using ft_strjoin
		// Otherwise, duplicate buf using ft_strdup
		if (str)
			str = ft_strjoin(str, buf);
		else
			str = ft_strdup(buf);
		return (str);
	}
	else if (cut > 0)
	{
		// If str is not NULL and str[cut] is not NULL, duplicate the substring starting from str + cut using ft_strdup
		// Free str and assign the duplicated substring to str
		if (str && str[cut])
		{
			temp = ft_strdup(str + cut);
			free(str);
			str = temp;
			return (NULL);
		}
		// If str is not NULL and str[cut] is NULL, free str
		free(str);
	}
	else if (cut == -1 && str)
		// If cut is -1 and str is not NULL, free str
		free(str);
	return ((void)(str = NULL), NULL);
}

static char	*extracted_line(char *line, char *str, char *buf, int cut)
{
	free(buf);
	if (cut)
	{
		// If cut is true, extract the line from str up to the first occurrence of '\n' using ft_substr
		// Update str by removing the extracted line using stralloc with a cut value equal to the length of the extracted line plus 1
		line = ft_substr(str, 0, ft_strchr(str, '\n') - str);
		stralloc(NULL, ft_strlen(line) + 1);
	}
	else
	{
		// If cut is false, duplicate the entire str using ft_strdup
		// Update str by freeing it and setting it to NULL using stralloc with a cut value of -1
		line = ft_strdup(str);
		stralloc(NULL, -1);
	}
	return (line);
}

static char	*last_line(char *str, char *line, char *buf)
{
	str = stralloc(buf, 0);
	if (str && ft_strchr(str, '\n'))
		// If str is not NULL and contains '\n', extract the line from str using extracted_line with a cut value of 1
		return (extracted_line(line, str, buf, 1));
	else if (str && ft_strlen(str) > 0)
		// If str is not NULL and its length is greater than 0, extract the line from str using extracted_line with a cut value of 0
		return (extracted_line(line, str, buf, 0));
	else
		// If str is NULL or its length is 0, update str by freeing it and setting it to NULL using stralloc with a cut value of -1
		return ((void)stralloc(NULL, -1), free(buf), NULL);
}

char	*get_next_line(int fd)
{
	char		*str;
	char		*line;
	char		*buf;
	int			rd;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		// If the file descriptor is invalid, BUFFER_SIZE is non-positive, or read returns a negative value, return NULL
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
			// If str is not NULL and contains '\n', extract the line from str using extracted_line with a cut value of 1
			return (extracted_line(line, str, buf, 1));
	}
	if (rd == 0)
		// If read returns 0, update str by freeing it and setting it to NULL using last_line
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