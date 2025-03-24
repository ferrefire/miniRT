/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:48:45 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 15:59:01 by ferre         ########   odam.nl         */
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
	d = -(plane.normal.x * plane.position.x + plane.normal.y
			* plane.position.y + plane.normal.z * plane.position.z);
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
	t_hit		hit_info;
	t_axis_vecs	a;
	float		t;
	float		cylinder_d;

	hit_info.intersected = 0;
	a.base_vec = sub(point, cylinder.position);
	t = dot(a.base_vec, cylinder.axis);
	a.axis_vec = mult(cylinder.axis,
			clamp(t, cylinder.h * -0.5, cylinder.h * 0.5));
	a.axis_p = add(cylinder.position, a.axis_vec);
	cylinder_d = distance(point, a.axis_p) - cylinder.radius;
	if (cylinder_d <= 0.0 && t >= cylinder.h * -0.5 && t <= cylinder.h * 0.5)
	{
		hit_info.intersected = 1;
		hit_info.position = cylinder.position;
		hit_info.normal = normalize(sub(point, a.axis_p));
		hit_info.color = cylinder.color;
	}
	hit_info.distance = abso(cylinder_d);
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
	t_var				x;
	t_closest_vectors	c;

	x.i = 0;
	c.closest_distance = 10000.0;
	while (x.i < scene.shapes.cylinder_count)
	{
		c.v.base_vec = sub(point, scene.shapes.cylinders[x.i].position);
		x.t = dot(c.v.base_vec, scene.shapes.cylinders[x.i].axis);
		c.v.axis_vec = mult(scene.shapes.cylinders[x.i].axis, x.t);
		c.v.axis_p = add(scene.shapes.cylinders[x.i].position, c.v.axis_vec);
		c.current_distance = distance_squared(
				point, c.v.axis_p) - (scene.shapes.cylinders[x.i].radius
				* scene.shapes.cylinders[x.i].radius);
		if (c.current_distance < c.closest_distance)
		{
			c.closest_distance = c.current_distance;
			c.closest_cylinder = c.v.axis_p;
			c.closest_radius = scene.shapes.cylinders[x.i].radius;
		}
		x.i++;
	}
	if (c.closest_distance < 10000.0)
		return (distance(point, c.closest_cylinder) - c.closest_radius);
	return (c.closest_distance);
}
