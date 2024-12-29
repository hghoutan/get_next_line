/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 18:38:49 by hghoutan          #+#    #+#             */
/*   Updated: 2024/12/29 22:40:21 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*handle_concat(char *buffer, char *str)
{
	char	*temp;

	temp = ft_strjoin(buffer, str);
	if (!temp)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (temp);
}

char	*read_file_part(int fd, char *remainder, char *buffer)
{
	int	byte_read;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (NULL);
		if (byte_read == 0 && !*remainder)
			return (NULL);
		buffer[byte_read] = 0;
		remainder = handle_concat(remainder, buffer);
		if (!remainder || *remainder == '\0')
			return (NULL);
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	return (remainder);
}

char	*read_from_file(int fd, char *remainder)
{
	char	*buffer;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(remainder);
		return (NULL);
	}
	temp = read_file_part(fd, remainder, buffer);
	if (!temp)
	{
		free(remainder);
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (temp);
}

char	*extract_line(char *buffer, char **line, char **new_buffer)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (NULL);
	*line = malloc(i + 2);
	if (!*line)
		return (NULL);
	ft_strncpy(*line, buffer, i + 1);
	(*line)[i + 1] = '\0';
	*new_buffer = malloc(ft_strlen(buffer) - i);
	if (!*new_buffer)
		return (NULL);
	j = 0;
	i++;
	while (buffer[i])
		(*new_buffer)[j++] = buffer[i++];
	(*new_buffer)[j] = '\0';
	return (*new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;
	char		*new_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[fd])
	{
		buffer[fd] = ft_calloc(1, 1);
		if (!buffer[fd])
			return (NULL);
	}
	buffer[fd] = read_from_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	if (!extract_line(buffer[fd], &line, &new_buffer))
	{
		line = buffer[fd];
		buffer[fd] = NULL;
		return (line);
	}
	free(buffer[fd]);
	buffer[fd] = new_buffer;
	return (line);
}
