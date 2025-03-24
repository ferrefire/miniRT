/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting2.c                                     :+:    :+:           */
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
