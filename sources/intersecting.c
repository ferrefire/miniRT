/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:49:31 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/12 22:08:44 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "intersecting.h"
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
	float d;
	float side;

	d = -(plane.normal.x * plane.position.x + plane.normal.y * plane.position.y + plane.normal.z * plane.position.z);
	side = plane.normal.x * point.x + plane.normal.y * point.y + plane.normal.z * point.z + d;
	if (side <= 0.0) return (1);
	return (0);
}

t_hit intersectingCylinder(t_vec point, t_cylinder cylinder)
{
	t_hit hitInfo;
	t_vec baseVec;
	t_vec axisVec;
	t_vec axisPoint;
	float t;

	hitInfo.intersected = 0;
	hitInfo.color = cylinder.color;
	baseVec = sub(point, cylinder.position);
	t = dot(baseVec, cylinder.axis);
	if (t < cylinder.height * -0.5 || t > cylinder.height * 0.5)
		return (hitInfo);
	axisVec = mult(cylinder.axis, t);
	axisPoint = add(cylinder.position, axisVec);
	hitInfo.normal = normalize(sub(point, axisPoint));
	if (distance(point, axisPoint) <= cylinder.radius)
	{
		hitInfo.intersected = 1;
		return (hitInfo);
	}
	return (hitInfo);
}