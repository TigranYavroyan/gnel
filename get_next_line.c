/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyavroya <tyavroya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:25:40 by tyavroya          #+#    #+#             */
/*   Updated: 2024/02/19 18:03:02 by tyavroya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen (char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\n' && str[count] != '\0')
	{
		++count;
	}
	return (count);
}

void	ft_realloc(char **str, int from, int to)
{
	char	*new_string;
	int		offset;
	size_t	i;

	i = 0;
	offset = to - from;
	new_string = (char *) malloc (offset + 1);
	while (i < offset && (*str)[from] != '\0')
	{
		new_string[i] = (*str)[from];
		++from;
		++i;
	}
	new_string[offset] = '\0';
	free(*str);
	*str = new_string;
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*new_line;
	int			i;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	i = 0;
	str = (char *) malloc(BUFFER_SIZE + 1);
	read(fd, str, BUFFER_SIZE);
	str[BUFFER_SIZE] = '\0';
	printf("static memory -> %s", str);
	str[BUFFER_SIZE] = '\0';
	new_line = (char *) malloc(ft_strlen(str) + 1);
	while (str[i] != '\n' && str[i] != '\0')
	{
		new_line[i] = str[i];
		++i;
	}
	new_line[i] = '\0';
	ft_realloc(&str, i + 1, BUFFER_SIZE);
	return (new_line);
}

int main () {
	int fd = open("text.txt", O_RDONLY);
	const char* str = get_next_line(fd);
	printf("\n%s\n", str);
	str = get_next_line(fd);
	printf("\n%s\n", str);

	close(fd);
}

