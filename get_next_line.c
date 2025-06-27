/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wschafer <wschafer@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 11:55:43 by wschafer          #+#    #+#             */
/*   Updated: 2025/06/10 11:55:47 by wschafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*cache = NULL;
	char			*str;
	char			*newline;
	ssize_t			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		newline = ft_strchr(cache, '\n');
		if (newline)
			return get_line(&cache, newline);
		bytes = read_line(fd, &cache);
		if (bytes == -1)
			return (NULL);
		if (bytes == 0)
		{
			if (cache && *cache != '\0')
			{
				str = cache;
				cache = NULL;
				return (str);
			}
			free (cache);
			cache = NULL;
			return (NULL);
		}
	}
}
ssize_t	read_line(int fd, char **cache)
{
	char	*buffer;
	char	*tmp;
	ssize_t	bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	bytes = read(fd, buffer, BUFFER_SIZE);
	if (bytes > 0)
	{
		buffer[bytes] = '\0';
		tmp = ft_strjoin(*cache, buffer);
		if (!tmp)
		{
			free(*cache);
			*cache = NULL;
			free(buffer);
			return (-1);
		}
	}
	free (*cache);
	*cache = tmp;
	return (bytes);
}

char	*get_line(char **cache, char *newline)
{
	char	*str;
	char	*rest;
	int		len;

	len = newline - *cache + 1;
	str = ft_substr(*cache, 0, len);
	rest = ft_strdup(newline + 1);
	free (*cache);
	*cache = rest;
	return (str);
}



//int read(int fileDescriptor, void *buffer, size_t bytesToRead)

int	main()
{
	char	*str;
	int		fd;

	fd = open("text.txt", O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (str)
			printf("%s", str);
		else
			break;
	}
	close(fd);
	return (0);
}
