/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:48:39 by macbook           #+#    #+#             */
/*   Updated: 2024/12/22 21:22:16 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

char    *get_next_line(int fd) {
  
  static char* reminder;
  char *temp;
  char *buffer;
  char *line;
  int i;
  int count;

  if(!reminder)
        reminder = malloc(1);
  if (!reminder)
      return (NULL);

  buffer = malloc(BUFFER_SIZE + 1);
  if (!buffer)
      return (NULL);
  
  while ((count = read(fd, buffer, BUFFER_SIZE)) > 0) {
    buffer[count] = '\0';

    temp = reminder;
    reminder = malloc(ft_strlen(temp) + count + 1);

    if (!reminder)
    {
        free(temp);
        free(buffer);
        return (NULL);
    }

    ft_strcpy(reminder, temp);
    ft_strcat(reminder, buffer);
    free(temp);
    
    
    i = 0;
    while (reminder[i]){
      if (reminder[i] == '\n')
      {
        line = malloc(i + 2);
        if (!line) 
        {
          free(line);
          free(buffer);
          return (NULL);
        }
        ft_strncpy(line, reminder, i + 1);
        line[i + 1] = '\0';
        
        
        return (line);
      }
      i++;
    }
  }
  return (line);
}

char	*ft_join_and_free(char *text, char *buffer)
{
	char	*temp;

	temp = ft_strjoin(text, buffer);
	free(text);
	return (temp);
}

char *read_from_file(int fd, char *remainder) {
  int byte_read;
  char *buffer;

  if (!remainder){
    remainder = malloc(1);
    remainder[0] = '\0';
  }
  buffer = malloc(BUFFER_SIZE + 1);
  if (!buffer)
    return (NULL);
  byte_read = 1;
  while (byte_read > 0) {
    byte_read = read(fd, buffer, BUFFER_SIZE);
    if (byte_read == -1)
		{
			free(remainder);
			free(buffer);
			return (NULL);
		}
    buffer[byte_read] = 0;
    remainder = ft_join_and_free(remainder, buffer);
    if (ft_strchr(remainder, '\n'))
			break;
  }
  free(buffer);
  return (remainder);
}

char *extract_line(char *buffer) {
  int i;
  char *line;

  while(buffer[i]) {
    if (buffer[i] == '\n')
    {
      line = malloc(i + 2);
      if (!line)
      {
        free(line);
        free(buffer);
        return (NULL);
      }

      line = ft_strncpy(line, buffer, i + 1);
      line[i + 1] = '\0';
      return (line);
    }
    i++;
  }
  return (NULL);
}

char *skip_line(char* buffer) {
  int i;
  int j;
  char *new_buffer;

  i = 0;
  j = 0;
  while (buffer[i] && buffer[i] != '\n')
    i++;

  new_buffer = malloc(ft_strlen(buffer) - i + 1);
  while (buffer[++i])
    new_buffer[j++] = buffer[i];
  new_buffer[j] = '\0';
  return (new_buffer);
}

char *get_next_line2(int fd) {
  static char *buffer;
  char *line;
  
  buffer = read_from_file(fd, buffer);
  if(!buffer)
    return (NULL);
  line = extract_line(buffer);
  buffer = skip_line(buffer);
  return (line);
}
int main(void) {
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1)
        return (1);

    printf("-%s\n", get_next_line2(fd));
    printf("-%s\n", get_next_line2(fd));
    printf("-%s\n", get_next_line2(fd));
    printf("-%s\n", get_next_line2(fd));
   
    // get_next_line2(fd);
    // get_next_line2(fd);
    // get_next_line2(fd);
    //get_next_line2(fd);
    // printf("-%s\n", get_next_line2(fd));
    // printf("-%s\n", get_next_line2(fd));
    // get_next_line(fd);
    // get_next_line(fd);
    // printf("%s\n", );

    close(fd);
    return (0);
}