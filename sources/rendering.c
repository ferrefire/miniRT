/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:18:41 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 20:31:05 by ferre         ########   odam.nl         */
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

int	color_to_int(t_vec color)
{
	return (255 << 24 | (int)color.x << 16 | (int)color.y << 8 | (int)color.z);
}

void	render_pixel(int x, int y, t_vec color, t_data *data)
{
	char	*dst;

	dst = data->mlx_data.image_data.address + (y
			* data->mlx_data.image_data.line + x
			* (data->mlx_data.image_data.bpp / 8));
	*(unsigned int *)dst = color_to_int(color);
}

int	render_image(t_data *data)
{
	t_ray	current_ray;
	t_vec	pixel_color;

	if (data->y >= HEIGHT)
		return (1);
	current_ray = initiate_ray(data->x, data->y, data->scene_data.camera);
	pixel_color = trace_ray(current_ray, data->scene_data);
	render_pixel(data->x, data->y, pixel_color, data);
	data->x += 1;
	if (data->x >= WIDTH)
	{
		data->x = 0;
		data->y += 1;
		if (data->y >= HEIGHT)
			printf("image rendered in %ld seconds\n",
				(time(NULL) - data->start));
		mlx_put_image_to_window(data->mlx_data.mlx,
			data->mlx_data.win,
			data->mlx_data.image_data.image, 0, 0);
	}
	return (0);
}

t_vec	trace_ray(t_ray ray, t_scene_data scene)
{
	t_hit	hit_info;
	t_vec	light_normal;
	float	shadow;
	float	light_distance;
	float	diffuse;
	t_vec	specular_color;
	float	closest;
	t_vec	reflection_normal;
	float	specular;

	while (distance_squared(ray.position, ray.origin)
		< scene.camera.far * scene.camera.far)
	{
		hit_info = check_intersections(ray, scene);
		if (hit_info.intersected)
		{
			light_normal = normalize(sub(scene.light.source, ray.position));
			shadow = in_shadow((t_ray){ray.position, light_normal, ray.position,
					scene.light.source,
					distance(ray.position, scene.light.source)}, scene);
			light_distance = 1.0;
			diffuse = clamp(dot(hit_info.normal, light_normal)
					* light_distance * shadow, scene.ambient.intensity, 1.0);
			specular_color = BLACK;
			reflection_normal = sub(mult(hit_info.normal, 2.0
						* dot(light_normal, hit_info.normal)),
					light_normal);
			specular = clamp(dot(mult(ray.direction,
							-1.0), reflection_normal), 0.0, 1.0);
			specular = pow(specular, 4.0);
			specular_color = mult(WHITE, specular);
			return (clamp_vec(mult(add(hit_info.color,
							specular_color), diffuse), 0.0, 255.0));
		}
		closest = clamp(hit_info.distance, scene.step, scene.camera.far);
		ray.position = add(ray.position, mult(ray.direction, closest));
	}
	return (BLACK);
}

float	in_shadow(t_ray ray, t_scene_data scene)
{
	t_hit	hit_info;
	int		away;
	float	closest;

	away = 0;
	ray.position = add(ray.position, mult(ray.direction, 0.1));
	while (distance_squared(ray.position, ray.origin) < ray.max * ray.max)
	{
		hit_info = check_intersections(ray, scene);
		if (hit_info.intersected)
			return (0.0);
		closest = clamp(hit_info.distance, scene.step, ray.max);
		ray.position = add(ray.position, mult(ray.direction, closest));
	}
	return (1.0);
}
