/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:37:59 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 13:38:30 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "vector.h"
#include "libft.h"

#include <stddef.h>
#include <stdio.h>

void printVector(t_vec vec)
{
	printf("x: %f\ty: %f\tz: %f\n", vec.x, vec.y, vec.z);
}

float clamp(float value, float min, float max)
{
	if (value < min) return (min);
	else if (value > max) return (max);
	else return (value);
}

void	*allocate_memory(size_t buffer_size)
{
	void	*buffer;

	buffer = (void *)malloc(buffer_size);
	if (!buffer)
    return (NULL);
	return (buffer);
}

void	free_memory(void *buffer)
{
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
}

double ft_atof(const char *str)
{
  double result;
  double sign;
  double divisor;

  result = 0.0;
  sign = 1.0;
  divisor = 10.0;

  if (*str == '-')
  {
    sign = -1.0;
    str++;
  }
  
  else if (*str == '+')
    str++;
  
  while (*str >= '0' && *str <= '9')
  {
    result = result * 10.0 + (*str - '0');
    str++;
  }

  if (*str == '.')
  {
    str++;
    while (*str >= '0' && *str <= '9')
    {
      result += (*str - '0') / divisor;
      divisor *= 10.0;
      str++;
    }
  }
  return (sign * result);
}

void	*memory_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void      *new_ptr;
  size_t    copy_size;

	if (new_size == 0)
	{
		free_memory(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (allocate_memory(new_size));
	new_ptr = allocate_memory(new_size);
	if (new_ptr == NULL)
		return (NULL);

  if (old_size < new_size)
    copy_size = old_size;
  else
    copy_size = new_size;

	ft_memcpy(new_ptr, ptr, copy_size);
	free_memory(ptr);
	return (new_ptr);
}
