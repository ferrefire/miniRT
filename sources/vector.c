/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:30:45 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/10 21:35:04 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include "math.h"

float length(t_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec normalize(t_vec vec)
{
	t_vec normalized;
	float magnitude;

	magnitude = length(vec);
	normalized.x = vec.x / magnitude;
	normalized.y = vec.y / magnitude;
	normalized.z = vec.z / magnitude;

	return (normalized);
}