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

char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcat(char *dest, const char *src, size_t dsize);


size_t	BUFFER_SIZE = 1024;

char	*get_next_line(int fd)
{
	int				len = 0;
	char			*buffer;
	static	char	*cache = NULL;
	int				i;
	char			*str;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (NULL);
	i = 1;
	while (1)
	{
		len = ft_strchr(cache, BUFFER_SIZE);
		if (len)
		{
			str = ft_substr(buffer, len);
			cache = ft_strcat(cache, buffer, len);
			return (str);
		}
		buffer = malloc(BUFFER_SIZE + 1);
		if (read (fd, buffer, BUFFER_SIZE))
		{
			len = ft_strchr(cache, BUFFER_SIZE);
			if (len)
			{
				str = ft_substr(buffer, len);
				cache = ft_strcat(cache, buffer, len);
				return (str);
			}
			ft_strcat(cache, buffer, len);
		}
		return (cache);
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
