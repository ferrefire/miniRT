/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:49:31 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/12 23:29:29 by ferre         ########   odam.nl         */
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
	//centerDistance = distanceSquared(point, sphere.center);
	//if (centerDistance <= sphere.radius * sphere.radius) 
	//	return (1);
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
	if (distanceSquared(point, axisPoint) <= cylinder.radius * cylinder.radius)
	{
		hitInfo.intersected = 1;
		return (hitInfo);
	}
	return (hitInfo);
}

float closestSphere(t_vec point, t_scene_data scene)
{
	t_vec closestSphere;
	float closestDistance;

	closestDistance = 10000.0;
	for (int i = 0; i < scene.shapes.sphereCount; i++)
	{
		float currentDistance = distanceSquared(point, scene.shapes.spheres[i].center);
		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			closestSphere = scene.shapes.spheres[i].center;
		}
	}

	if (closestDistance < 10000.0)
		return (distance(point, closestSphere));
}

float closestCylinder(t_vec point, t_scene_data scene)
{
	t_vec closestCylinder;
	float closestDistance;

	closestDistance = 10000.0;
	for (int i = 0; i < scene.shapes.cylinderCount; i++)
	{
		t_vec baseVec = sub(point, scene.shapes.cylinders[i].position);
		float t = dot(baseVec, scene.shapes.cylinders[i].axis);
		t_vec axisVec = mult(scene.shapes.cylinders[i].axis, t);
		t_vec axisPoint = add(scene.shapes.cylinders[i].position, axisVec);

		float currentDistance = distanceSquared(point, axisPoint);
		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			closestCylinder = axisPoint;
		}
	}

	if (closestDistance < 10000.0)
		return (distance(point, closestCylinder));
}

float closestShape(t_vec point, t_scene_data scene)
{
	float nearestSphere;
	float nearestCylinder;

	nearestSphere = closestSphere(point, scene);
	nearestCylinder = closestCylinder(point, scene);

	if (nearestSphere < nearestCylinder)
		return (nearestSphere);
	else
		return (nearestCylinder);
}