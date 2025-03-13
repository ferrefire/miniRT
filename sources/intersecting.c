/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:49:31 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 02:12:05 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "intersecting.h"
#include "vector.h"
#include "utilities.h"

int intersectingSphere(t_vec point, t_sphere sphere)
{
	float centerDistance;

	//centerDistance = distance(point, sphere.center);
	//if (centerDistance <= sphere.radius)
	//	return (1);
	centerDistance = distanceSquared(point, sphere.center);
	if (centerDistance <= sphere.radius * sphere.radius) 
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
	if (distanceSquared(point, axisPoint) <= cylinder.radius * cylinder.radius)
	{
		hitInfo.intersected = 1;
		return (hitInfo);
	}
	return (hitInfo);
}

float closestSphere(t_vec point, t_scene_data scene)
{
	//t_vec closestSphere;
	//float closestRadius;
	float closestDistance;

	closestDistance = 10000.0;
	for (int i = 0; i < scene.shapes.sphereCount; i++)
	{
		float currentDistance = distanceSquared(point, scene.shapes.spheres[i].center) - 
			(scene.shapes.spheres[i].radius * scene.shapes.spheres[i].radius);
		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			//closestSphere = scene.shapes.spheres[i].center;
			//closestRadius = scene.shapes.spheres[i].radius;
		}
	}

	//if (closestDistance < 10000.0)
	//	return (distance(point, closestSphere) - closestRadius);
	return (closestDistance);
}

float closestCylinder(t_vec point, t_scene_data scene)
{
	//t_vec closestCylinder;
	float closestDistance;
	//float closestRadius;

	closestDistance = 10000.0;
	for (int i = 0; i < scene.shapes.cylinderCount; i++)
	{
		t_vec baseVec = sub(point, scene.shapes.cylinders[i].position);
		float t = dot(baseVec, scene.shapes.cylinders[i].axis);
		t_vec axisVec = mult(scene.shapes.cylinders[i].axis, t);
		t_vec axisPoint = add(scene.shapes.cylinders[i].position, axisVec);

		float currentDistance = distanceSquared(point, axisPoint) -
			(scene.shapes.cylinders[i].radius * scene.shapes.cylinders[i].radius);
		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
			//closestCylinder = axisPoint;
			//closestRadius = scene.shapes.cylinders[i].radius;
		}
	}

	//if (closestDistance < 10000.0)
	//	return (distance(point, closestCylinder) - closestRadius);
	return (closestDistance);
}

float closestPlane(t_vec point, t_scene_data scene)
{
	//t_vec closestPlane;
	float closestDistance;

	closestDistance = 10000.0;
	for (int i = 0; i < scene.shapes.planeCount; i++)
	{
		float d = -(scene.shapes.planes[i].normal.x * scene.shapes.planes[i].position.x + 
			scene.shapes.planes[i].normal.y * scene.shapes.planes[i].position.y + 
			scene.shapes.planes[i].normal.z * scene.shapes.planes[i].position.z);
		float side = scene.shapes.planes[i].normal.x * point.x + scene.shapes.planes[i].normal.y * 
			point.y + scene.shapes.planes[i].normal.z * point.z + d;
		float currentDistance = abso(side);
		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
		}
	}

	//if (closestDistance < 10000.0)
	//	return (distance(point, closestPlane));
	return (closestDistance * closestDistance * closestDistance);
}

float closestShape(t_vec point, t_scene_data scene)
{
	float nearestPlane;
	float nearestSphere;
	float nearestCylinder;

	nearestPlane = closestPlane(point, scene);
	if (nearestPlane <= 1.0) return (nearestPlane);
	nearestSphere = closestSphere(point, scene);
	if (nearestSphere <= 1.0) return (nearestSphere);
	nearestCylinder = closestCylinder(point, scene);

	if (nearestPlane < nearestSphere && nearestPlane < nearestCylinder)
		return (nearestPlane);
	else if (nearestSphere < nearestCylinder)
		return (nearestSphere);
	else
		return (nearestCylinder);
}