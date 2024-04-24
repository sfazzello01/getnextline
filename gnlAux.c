#include "get_next_line.h"

char	*stralloc(char *buf, int cut)
{
	static char	*str;

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
			char *temp = ft_strdup(str + cut);
			free(str);
			str = temp;
			return (NULL);
		}
		free(str);
	}
	else if (cut == -1 && str)
		free(str);
	str = NULL;
	return (NULL);
}

char	*extract_line(char *str, char *ptr)
{
	char 		*line;

	line =  ft_substr(str, 0, ptr - str);
	return (line);
}
