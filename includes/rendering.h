/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:20:55 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 16:09:07 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "minirt.h"
# include "ray.h"
# include "vector.h"

typedef struct s_hit
{
	int		intersected;
	t_vec	position;
	t_vec	normal;
	t_vec	color;
	float	distance;
}	t_hit;

typedef struct s_floats
{
	float	shadow;
	float	light_distance;
	float	diffuse;
	float	closest;
	float	spec;
}	t_floats;

typedef struct s_vecs
{
	t_vec	light_norm;
	t_vec	specular_color;
	t_vec	reflection_normal;
}	t_vecs;

t_vec	fwhite(void);
t_vec	fblack(void);
t_vec	fred(void);
t_vec	fgreen(void);
t_vec	fblue(void);
int		color_to_int(t_vec color);
void	render_pixel(int x, int y, t_vec color, t_data *data);
int		render_image(t_data *data);
t_vec	trace_ray(t_ray ray, t_scene_data scene);
float	in_shadow(t_ray ray, t_scene_data scene);
t_hit	check_intersections(t_ray ray, t_scene_data scene);
t_hit	check_shape_intersections(t_ray ray, void *shapes, int count,
			t_hit (*intersect_func)(t_vec, void *));

#endif
