/*
** get_next_line.c for get_next_line in /home/wargni_y/TEK1/CPE/CPE_2015_getnextline
**
** Made by Yoann Wargnier
** Login   <wargni_y@epitech.net>
**
** Started on  Tue Jun  7 15:28:40 2016 Yoann Wargnier
** Last update Fri Jun 24 17:34:56 2016 Yoann Wargnier
*/

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

int	my_strlen(char *str)
{
  int	i;

  i = 0;
  if (str[i] == '\0')
    return (0);
  while (str[i] != '\0')
    i = i + 1;
  return (i);
}

char	*re_malloc(char *str, int size)
{
  int	i;
  char	*new_malloc;

  i = 0;
  if ((new_malloc = malloc(sizeof(char) * (my_strlen(str) + size + 1))) == NULL)
    return (NULL);
  while (str[i] != '\0')
    {
      new_malloc[i] = str[i];
      i = i + 1;
    }
  new_malloc[i] = '\0';
  free(str);
  return (new_malloc);
}

int		my_strcat(char *out, char *buff)
{
  int		i;
  int		k;

  i = 0;
  while (out[i] != '\0')
    i = i + 1;
  while (buff[0] != '\0' && buff[0] != '\n')
    {
      out[i] = buff[0];
      k = -1;
      while (buff[++k] != '\0')
	buff[k] = buff[k + 1];
      i = i + 1;
    }
  out[i] = '\0';
  if (buff[0] == '\n')
    {
      k = -1;
      while (buff[++k] != '\0')
	buff[k] = buff[k + 1];
      return (42);
    }
  return (0);
}

char		*get_next_line(const int fd)
{
  static char	buff[READ_SIZE + 1];
  char		*out;
  int		ret;

  if (!(out = malloc(sizeof(char) * READ_SIZE + (READ_SIZE + 1))))
    return (NULL);
  out[0] = '\0';
  if (buff[0] != '\0')
    {
      if (my_strcat(out, buff) == 42)
	  return (out);
    }
  while ((ret = read(fd, buff, READ_SIZE)) >= 0)
    {
      buff[ret] = 0;
      if (my_strcat(out, buff) == 42)
	  return (out);
      if (ret == 0)
	return ((out[0] == '\0') ? NULL : out);
      out = re_malloc(out, ret);
    }
  return (NULL);
}
