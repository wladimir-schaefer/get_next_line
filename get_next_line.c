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

size_t	BUFFER_SIZE = 1024;

char	*get_next_line(int fd)
{

	char			*buffer;
	static	char	*cache = NULL;
	int				i;
	char			*str;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);

	while (1)
	{
		if (ft_strchr(cache, '\n'))
		{
			str = ft_substr(cache, 0, len);
			cache = strdup(cache);
			return (str);
		}
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (NULL);
		if (read(fd, buffer, BUFFER_SIZE))
		{
			buffer[BUFFER_SIZE] = '\0';
			cache = ft_strjoin(cache, buffer);
		}
	}
	return (NULL);
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
