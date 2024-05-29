/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brvasque <brvasque@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 08:25:01 by brvasque          #+#    #+#             */
/*   Updated: 2024/04/16 17:27:20 by brvasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = (char *)s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
}

char	*ft_next_line(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*next_line;

	i = 0;
	j = -1;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	next_line = malloc(ft_strlen(&buffer[i]) + 1);
	if (!next_line)
		return (free(next_line), freeline(&buffer));
	while (buffer[i])
		next_line[++j] = buffer[i++];
	next_line[j + 1] = '\0';
	freeline(&buffer);
	return (next_line);
}

char	*read_line(int fd, char *buffer)
{
	char	*tmp;
	int		bytes_num;

	bytes_num = 1;
	while (!ft_strchr(buffer, '\n') && bytes_num > 0)
	{
		tmp = malloc(BUFFER_SIZE + 1);
		if (!tmp)
			return (free(tmp), freeline(&buffer));
		ft_bzero(tmp, BUFFER_SIZE + 1);
		bytes_num = read(fd, tmp, BUFFER_SIZE);
		if (bytes_num < 0)
			return (free(tmp), freeline(&buffer));
		buffer = ft_strjoin(buffer, tmp);
		if (!buffer)
			return (freeline(&buffer));
	}
	return (buffer);
}

char	*ft_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer || (buffer && !ft_strchr(buffer, '\n')))
		buffer = read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	if (!line)
		return (free (line), freeline(&buffer));
	buffer = ft_next_line(buffer);
	return (line);
}
/*
int main()
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd < 0)
	{
		printf("File Descriptor Empty");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return(0);
}*/
