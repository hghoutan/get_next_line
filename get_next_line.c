/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 18:48:39 by macbook           #+#    #+#             */
/*   Updated: 2024/12/22 19:00:17 by macbook          ###   ########.fr       */
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

int main(void) {
    int fd = open("file.txt", O_RDONLY);
    if (fd == -1)
        return (1);

    get_next_line(fd);
    get_next_line(fd);
    get_next_line(fd);
    // printf("%s\n", );

    close(fd);
    return (0);
}