/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:18:41 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 13:50:24 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "rendering.h"
#include "intersecting.h"
#include "ray.h"
#include "utilities.h"

int colorToInt(t_vec color)
{
	return (255 << 24 | (int)color.x << 16 | (int)color.y << 8 | (int)color.z);
}

void renderPixel(int x, int y, t_vec color, t_data *data)
{
	mlx_pixel_put(data->mlx_data.mlx, data->mlx_data.win, x, y, colorToInt(color));
}

void renderImage(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->mlx_data.height)
	{
		x = 0;
		while (x < data->mlx_data.width)
		{
			//t_vec pixelColor = (t_vec){(int)(((float)x / (float)data->mlx_data.width) * 255), (int)(((float)y / (float)data->mlx_data.height) * 255), 255};
			t_ray currentRay = initiateRay(x, y, data->scene_data.camera);
			t_vec pixelColor = traceRay(currentRay, data->scene_data);
			renderPixel(x, y, pixelColor, data);
			x++;
		}
		y++;
	}
	
	mlx_loop(data->mlx_data.mlx);
}

t_vec traceRay(t_ray ray, t_scene_data scene)
{
	int iterations;
	t_sphere sphere;
	sphere.center = (t_vec){0, 0, 10};
	sphere.radius = 2.5;
	sphere.color = WHITE;

	iterations = 0;
	while (iterations < 200)
	{
		if (intersectingSphere(ray.position, sphere))
		{
			float diffuse = clamp(dot(normalize(sub(ray.position, sphere.center)), scene.light.source), scene.ambient.intensity, 1.0);
			return (mult(WHITE, diffuse));
		}
		ray.position = add(ray.position, mult(ray.direction, 0.1));
		iterations++;
	}
	
	return (BLACK);
}