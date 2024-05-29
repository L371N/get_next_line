/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brvasque <brvasque@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:05:49 by brvasque          #+#    #+#             */
/*   Updated: 2024/04/16 16:14:25 by brvasque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freeline(char **buffer)
{
	if (*buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	return (NULL);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	if (str)
	{
		while (str[i])
			i++;
	}
	return (i);
}

int	ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i] != (char)c && str[i] != '\0')
		{
			i++;
			if (str[i] == (char)c)
				return (1);
		}
	}
	return (0);
}

char	*ft_strjoin(char *buffer, char *tmp)
{
	size_t	i;
	size_t	buffersize;
	char	*dest;

	i = 0;
	if (!buffer && !tmp)
		return (NULL);
	buffersize = ft_strlen(buffer);
	dest = malloc((buffersize + ft_strlen(tmp) + 1));
	if (!dest)
		return (free(tmp), freeline(&buffer));
	while (i < buffersize + ft_strlen(tmp))
	{
		if (i < buffersize)
			dest[i] = buffer[i];
		else
			dest[i] = tmp[i - buffersize];
		i++;
	}
	dest[i] = '\0';
	freeline(&buffer);
	free(tmp);
	return (dest);
}
