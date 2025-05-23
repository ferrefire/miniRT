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

void	print_vector(t_vec vec)
{
	printf("x: %f\ty: %f\tz: %f\n", vec.x, vec.y, vec.z);
}

float	clamp(float value, float min, float max)
{
	if (value < min)
		return (min);
	else if (value > max)
		return (max);
	else
		return (value);
}

float	abso(float value)
{
	if (value >= 0.0)
		return (value);
	else
		return (value * -1.0);
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
