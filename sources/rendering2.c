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

t_hit	check_intersections(t_ray ray, t_scene_data scene)
{
	t_hit	hit_info;
	float	closest;
	int		i;

	closest = 10000.0;
	i = 0;
	while (i < scene.shapes.plane_count)
	{
		hit_info = intersecting_plane(ray.position, scene.shapes.planes[i]);
		if (hit_info.intersected)
			return (hit_info);
		if (hit_info.distance < closest)
			closest = hit_info.distance;
		i++;
	}
	i = 0;
	while (i < scene.shapes.sphere_count)
	{
		hit_info = intersecting_sphere(ray.position, scene.shapes.spheres[i]);
		if (hit_info.intersected)
			return (hit_info);
		if (hit_info.distance < closest)
			closest = hit_info.distance;
		i++;
	}
	i = 0;
	while (i < scene.shapes.cylinder_count)
	{
		hit_info = intersecting_cylinder(ray.position, scene.shapes.cylinders[i]);
		if (hit_info.intersected)
			return (hit_info);
		if (hit_info.distance < closest)
			closest = hit_info.distance;
		i++;
	}
	hit_info.intersected = 0;
	hit_info.distance = closest;
	return (hit_info);
}
