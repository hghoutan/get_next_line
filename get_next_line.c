/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:48:39 by macbook           #+#    #+#             */
/*   Updated: 2024/12/28 17:28:36 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:48:39 by macbook           #+#    #+#             */
/*   Updated: 2024/12/27 22:35:22 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*buffer;
	char		*line;
	char		*new_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
	{
		buffer = ft_calloc(1, 1);
		if (!buffer)
			return (NULL);
	}
	buffer = read_from_file(fd, buffer);
	if (!buffer)
		return (NULL);
	if (!extract_line(buffer, &line, &new_buffer))
	{
		line = buffer;
		buffer = NULL;
		return (line);
	}
	free(buffer);
	buffer = new_buffer;
	return (line);
}

int	main(void)
{
	// char *str;
	int fd = open("file.txt", O_RDONLY);
	if (fd == -1)
		return (1);
	// while ((str = get_next_line(fd)) != NULL)
	// {
	// 	printf("-%s", str);
	// 	free(str);
	// }
	printf("Buffer is :-%s\n", get_next_line(fd));
	// printf("-%s\n", get_next_line(fd));
	// printf("-%s\n", get_next_line(fd));
	// printf("-%s\n", get_next_line(fd));
	// printf("-%s\n", get_next_line(fd));
	// printf("-%s\n", get_next_line(fd));
	// printf("-%s\n", get_next_line(fd));
	// get_next_line2(fd);
	// get_next_line2(fd);
	// get_next_line2(fd);
	// get_next_line2(fd);
	// printf("-%s\n", get_next_line2(fd));
	// printf("-%s\n", get_next_line2(fd));
	// get_next_line(fd);
	// get_next_line(fd);
	// printf("%s\n", );
	// str = get_next_line(fd);
	// free(str);
	// printf("Last :%s", str);
	close(fd);
	return (0);
}