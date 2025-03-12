/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:49:31 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/12 15:56:24 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector.h"

int intersectingSphere(t_vec point, t_sphere sphere)
{
	float centerDistance;

	centerDistance = distance(point, sphere.center);
	if (centerDistance <= sphere.radius) 
		return (1);
	return (0);
}

int intersectingPlane(t_vec point, t_plane plane)
{
	if (point.y <= plane.position.y)
		return (1);
	return (0);
}