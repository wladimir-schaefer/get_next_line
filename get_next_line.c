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
	char			*line;
	char			*buffer;
	static	char	*stored;

	if (fd == -1)
		return (NULL);
	stored = malloc(BUFFER_SIZE + 1);
	read (fd, stored, BUFFER_SIZE);
	line = stored;

	return (line);
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