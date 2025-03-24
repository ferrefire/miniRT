/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:37:01 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 16:49:55 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
# define UTILITIES_H

# include "vector.h"
# include <stdio.h>

void	print_vector(t_vec vec);
float	clamp(float value, float min, float max);
float	abso(float value);
void	*memory_realloc(void *ptr, size_t old_size, size_t new_size);
void	free_memory(void *buffer);
void	*allocate_memory(size_t buffer_size);
double	ft_atof(const char *str);

#endif
