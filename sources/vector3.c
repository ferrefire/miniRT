/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:30:45 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 16:46:09 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"
#include "math.h"
#include "utilities.h"

t_vec	clamp_vec(t_vec a, float min, float max)
{
	t_vec	result;

	result.x = clamp(a.x, min, max);
	result.y = clamp(a.y, min, max);
	result.z = clamp(a.z, min, max);
	return (result);
}
