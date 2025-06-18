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

int	str_check(const char *s);

size_t	BUFFER_SIZE = 1024;

char	*get_next_line(int fd)
{
	static	int		start = 0;
	static	char	*buffer = NULL;
	static	char	*stored = NULL;
	int				i;
	char			*str;

	if (fd == -1)
		return (NULL);
	i = 1;
	while (1)
	{
		if (!buffer)
			read (fd, buffer, BUFFER_SIZE);
		str = str_check(buffer);
		if (str)
		{

			return (str);
		}
		strcpy (str, stored);
	}


	return ();
}


int	str_check(const char *s)
{
	char	c;
	char	*str;
	size_t	len;
	size_t	i;

	c = '\n';
	len = 0;
	i = 0;
	while (s[len])
	{
		if (s[len] == '\n')
		{
			len += 2;
			str = malloc(len);
			if (!len)
				return (-1);
			while (i < len)
			{
				str[i] = s[i];
			}
			i++;
			str[len - 1] = '\n';
			str[len] = '\0';
		}
		len++;


	}
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
