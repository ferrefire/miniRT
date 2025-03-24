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

# define WHITE (t_vec){255, 255, 255}
# define BLACK (t_vec){0, 0, 0}
# define RED (t_vec){255, 0, 0}
# define GREEN (t_vec){0, 255, 0}
# define BLUE (t_vec){0, 0, 255}

typedef struct s_hit
{
	int		intersected;
	t_vec	position;
	t_vec	normal;
	t_vec	color;
	float	distance;
}	t_hit;

int		color_to_int(t_vec color);
void	render_pixel(int x, int y, t_vec color, t_data *data);
int		render_image(t_data *data);
t_vec	trace_ray(t_ray ray, t_scene_data scene);
float	in_shadow(t_ray ray, t_scene_data scene);
t_hit	check_intersections(t_ray ray, t_scene_data scene);

#endif
