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

#ifndef INTERSECTING_H
# define INTERSECTING_H

# include "minirt.h"
# include "vector.h"
# include "rendering.h"

t_hit	intersecting_sphere(t_vec point, t_sphere sphere);
t_hit	intersecting_plane(t_vec point, t_plane plane);
t_hit	intersecting_cylinder(t_vec point, t_cylinder cylinder);
float	closest_sphere(t_vec point, t_scene_data scene);
float	closest_cylinder(t_vec point, t_scene_data scene);
float	closest_plane(t_vec point, t_scene_data scene);
float	closest_shape(t_vec point, t_scene_data scene);

typedef struct s_axis_vecs
{
	t_vec	base_vec;
	t_vec	axis_vec;
	t_vec	axis_p;
}	t_axis_vecs;

typedef struct s_closest_vectors
{
	t_vec		closest_cylinder;
	float		closest_distance;
	float		closest_radius;
	float		current_distance;
	t_axis_vecs	v;
}	t_closest_vectors;

typedef struct s_var
{
	int		i;
	float	t;
}	t_var;

#endif
