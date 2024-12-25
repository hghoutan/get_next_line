/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:48:39 by macbook           #+#    #+#             */
/*   Updated: 2024/12/25 17:31:51 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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

char	*read_from_file(int fd, char *remainder)
{
	int		byte_read;
	char	*buffer;

	if (!remainder)
		remainder = ft_calloc(1, 1);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(remainder);
			free(buffer);
			return (NULL);
		}
		buffer[byte_read] = 0;
		remainder = handle_concat(remainder, buffer);
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	free(buffer);
	return (remainder);
}

char	*extract_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	while (buffer[i])
	{
		if (buffer[i] == '\n')
		{
			line = malloc(i + 2);
			if (!line)
			{
				free(buffer);
				return (NULL);
			}
			ft_strncpy(line, buffer, i + 1);
			line[i + 1] = '\0';
			return (line);
		}
		i++;
	}
	return (NULL);
}

char	*skip_line(char *buffer)
{
	int		i;
	int		j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	new_buffer = malloc(ft_strlen(buffer) - i + 1);
	if (!new_buffer)
		return (NULL);
	while (buffer[++i])
		new_buffer[j++] = buffer[i];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_from_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = extract_line(buffer);
	if (!line && *buffer)
	{
		line = buffer;
		buffer = NULL;
	}
	else
		buffer = skip_line(buffer);
	return (line);
}

// int	main(void)
// {
// 	char *str;
// 	int fd = open("file.txt", O_RDONLY);
// 	if (fd == -1)
// 		return (1);
// 	while ((str = get_next_line(fd)) != NULL)
// 	{
// 		printf("-%s\n", str);
// 	}
// 	// printf("-%s\n", get_next_line(fd));
// 	// printf("-%s\n", get_next_line(fd));
// 	// printf("-%s\n", get_next_line(fd));
// 	// printf("-%s\n", get_next_line(fd));
// 	// printf("-%s\n", get_next_line(fd));
// 	// get_next_line2(fd);
// 	// get_next_line2(fd);
// 	// get_next_line2(fd);
// 	// get_next_line2(fd);
// 	// printf("-%s\n", get_next_line2(fd));
// 	// printf("-%s\n", get_next_line2(fd));
// 	// get_next_line(fd);
// 	// get_next_line(fd);
// 	// printf("%s\n", );

// 	close(fd);
// 	return (0);
// }