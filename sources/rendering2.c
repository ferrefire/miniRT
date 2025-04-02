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

#include "mlx.h"
#include "minirt.h"
#include "rendering.h"
#include "intersecting.h"
#include "ray.h"
#include "utilities.h"
#include <math.h>
#include <stdio.h>

t_hit	check_planes(t_ray ray, t_scene_data scene, float *closest)
{
	t_hit	hit_info;
	int		i;

	i = 0;
	while (i < scene.shapes.plane_count)
	{
		hit_info = intersecting_plane(ray.pos, scene.shapes.planes[i]);
		if (hit_info.intersected)
			return (hit_info);
		if (hit_info.distance < *closest)
			*closest = hit_info.distance;
		i++;
	}
	hit_info.intersected = 0;
	return (hit_info);
}

t_hit	check_spheres(t_ray ray, t_scene_data scene, float *closest)
{
	t_hit	hit_info;
	int		i;

	i = 0;
	while (i < scene.shapes.sphere_count)
	{
		hit_info = intersecting_sphere(ray.pos, scene.shapes.spheres[i]);
		if (hit_info.intersected)
			return (hit_info);
		if (hit_info.distance < *closest)
			*closest = hit_info.distance;
		i++;
	}
	hit_info.intersected = 0;
	return (hit_info);
}

t_hit	check_cylinders(t_ray ray, t_scene_data scene, float	*closest)
{
	t_hit	hit_info;
	int		i;

	i = 0;
	while (i < scene.shapes.cylinder_count)
	{
		hit_info = intersecting_cylinder(ray.pos, scene.shapes.cylinders[i]);
		if (hit_info.intersected)
			return (hit_info);
		if (hit_info.distance < *closest)
			*closest = hit_info.distance;
		i++;
	}
	hit_info.intersected = 0;
	return (hit_info);
}

t_hit	check_intersections(t_ray ray, t_scene_data scene)
{
	t_hit	hit_info;
	float	closest;

	closest = 10000.0;
	hit_info = check_planes(ray, scene, &closest);
	if (hit_info.intersected)
		return (hit_info);
	hit_info = check_spheres(ray, scene, &closest);
	if (hit_info.intersected)
		return (hit_info);
	hit_info = check_cylinders(ray, scene, &closest);
	if (hit_info.intersected)
		return (hit_info);
	hit_info.intersected = 0;
	hit_info.distance = closest;
	return (hit_info);
}
