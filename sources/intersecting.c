/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:49:31 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 20:19:35 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "intersecting.h"
#include "vector.h"
#include "utilities.h"

t_hit	intersecting_sphere(t_vec point, t_sphere sphere)
{
	t_hit	hit_info;
	float	sphere_distance;

	hit_info.intersected = 0;
	sphere_distance = distance(point, sphere.center) - sphere.radius;
	if (sphere_distance <= 0.0)
	{
		hit_info.intersected = 1;
		hit_info.position = sphere.center;
		hit_info.normal = normalize(sub(point, sphere.center));
		hit_info.color = sphere.color;
	}
	hit_info.distance = abso(sphere_distance);
	return (hit_info);
}

t_hit	intersecting_plane(t_vec point, t_plane plane)
{
	t_hit	hit_info;
	float	d;
	float	side;

	hit_info.intersected = 0;
	d = -(plane.normal.x * plane.position.x + plane.normal.y * plane.position.y + plane.normal.z * plane.position.z);
	side = plane.normal.x * point.x + plane.normal.y
		* point.y + plane.normal.z * point.z + d;
	if (side <= 0.0)
	{
		hit_info.intersected = 1;
		hit_info.position = plane.position;
		hit_info.normal = plane.normal;
		hit_info.color = plane.color;
	}
	hit_info.distance = abso(side);
	return (hit_info);
}

t_hit	intersecting_cylinder(t_vec point, t_cylinder cylinder)
{
	t_hit	hit_info;
	t_vec	base_vec;
	t_vec	axis_vec;
	t_vec	axis_point;
	float	t;
	float	cylinder_distance;

	hit_info.intersected = 0;
	base_vec = sub(point, cylinder.position);
	t = dot(base_vec, cylinder.axis);
	axis_vec = mult(cylinder.axis,
			clamp(t, cylinder.height * -0.5, cylinder.height * 0.5));
	axis_point = add(cylinder.position, axis_vec);
	cylinder_distance = distance(point, axis_point) - cylinder.radius;
	if (cylinder_distance <= 0.0 && t >= cylinder.height * -0.5 && t <= cylinder.height * 0.5)
	{
		hit_info.intersected = 1;
		hit_info.position = cylinder.position;
		hit_info.normal = normalize(sub(point, axis_point));
		hit_info.color = cylinder.color;
	}
	hit_info.distance = abso(cylinder_distance);
	return (hit_info);
}

float	closest_sphere(t_vec point, t_scene_data scene)
{
	t_vec	closest_sphere;
	float	closest_distance;
	float	closest_radius;
	float	current_distance;
	int		i;

	i = 0;
	closest_distance = 10000.0;
	while (i < scene.shapes.sphere_count)
	{
		current_distance = distance_squared(point,
				scene.shapes.spheres[i].center)
			- (scene.shapes.spheres[i].radius
				* scene.shapes.spheres[i].radius);
		if (current_distance < closest_distance)
		{
			closest_distance = current_distance;
			closest_sphere = scene.shapes.spheres[i].center;
			closest_radius = scene.shapes.spheres[i].radius;
		}
		i++;
	}
	if (closest_distance < 10000.0)
		return (distance(point, closest_sphere) - closest_radius);
	return (closest_distance);
}

float	closest_cylinder(t_vec point, t_scene_data scene)
{
	t_vec	closest_cylinder;
	float	closest_distance;
	float	closest_radius;
	int		i;
	t_vec	base_vec;
	float	t;
	t_vec	axis_vec;
	t_vec	axis_point;
	float	current_distance;

	i = 0;
	closest_distance = 10000.0;
	while (i < scene.shapes.cylinder_count)
	{
		base_vec = sub(point, scene.shapes.cylinders[i].position);
		t = dot(base_vec, scene.shapes.cylinders[i].axis);
		axis_vec = mult(scene.shapes.cylinders[i].axis, t);
		axis_point = add(scene.shapes.cylinders[i].position, axis_vec);
		current_distance = distance_squared(point, axis_point)
			- (scene.shapes.cylinders[i].radius
				* scene.shapes.cylinders[i].radius);
		if (current_distance < closest_distance)
		{
			closest_distance = current_distance;
			closest_cylinder = axis_point;
			closest_radius = scene.shapes.cylinders[i].radius;
		}
		i++;
	}
	if (closest_distance < 10000.0)
		return (distance(point, closest_cylinder) - closest_radius);
	return (closest_distance);
}

float	closest_plane(t_vec point, t_scene_data scene)
{
	float	closest_distance;
	int		i;
	float	d;
	float	side;
	float	current_distance;

	closest_distance = 10000.0;
	while (i < scene.shapes.plane_count)
	{
		d = -(scene.shapes.planes[i].normal.x
				* scene.shapes.planes[i].position.x
				+ scene.shapes.planes[i].normal.y
				* scene.shapes.planes[i].position.y
				+ scene.shapes.planes[i].normal.z
				* scene.shapes.planes[i].position.z);
		side = scene.shapes.planes[i].normal.x
			* point.x + scene.shapes.planes[i].normal.y
			* point.y + scene.shapes.planes[i].normal.z * point.z + d;
		current_distance = abso(side);
		if (current_distance < closest_distance)
			closest_distance = current_distance;
		i++;
	}
	return (closest_distance);
}

float	closest_shape(t_vec point, t_scene_data scene)
{
	float	nearest_plane;
	float	nearest_sphere;
	float	nearest_cylinder;
	float	smallest_distance;

	smallest_distance = 0.01;
	nearest_plane = closest_plane(point, scene);
	if (nearest_plane <= smallest_distance)
		return (nearest_plane);
	nearest_sphere = closest_sphere(point, scene);
	if (nearest_sphere <= smallest_distance)
		return (nearest_sphere);
	nearest_cylinder = closest_cylinder(point, scene);
	if (nearest_plane < nearest_sphere && nearest_plane < nearest_cylinder)
		return (nearest_plane);
	else if (nearest_sphere < nearest_cylinder)
		return (nearest_sphere);
	else
		return (nearest_cylinder);
}
