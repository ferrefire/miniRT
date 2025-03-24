/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:37:59 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 16:50:00 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "vector.h"
#include "libft.h"

#include <stddef.h>
#include <stdio.h>

double	ft_atof(const char *str)
{
	t_atof	atof;

	atof.result = 0.0;
	atof.sign = 1.0;
	atof.divisor = 10.0;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			atof.sign = -1.0;
		str++;
	}
	while (*str >= '0' && *str <= '9')
		atof.result = atof.result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			atof.result += (*str++ - '0') / atof.divisor;
			atof.divisor *= 10.0;
		}
	}
	return (atof.sign * atof.result);
}

void	*memory_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

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
