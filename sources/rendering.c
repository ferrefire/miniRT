/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:18:41 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/10 23:24:00 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "rendering.h"
#include "intersecting.h"
#include "ray.h"

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
			t_vec pixelColor = traceRay(currentRay);
			renderPixel(x, y, pixelColor, data);
			x++;
		}
		y++;
	}
	
	mlx_loop(data->mlx_data.mlx);
}

t_vec traceRay(t_ray ray)
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
			float diffuse = dot(normalize(sub(ray.position, sphere.center)), (t_vec){0, 1, 0}) * 0.5 + 0.5;
			return (mult(WHITE, diffuse));
		}
		ray.position = add(ray.position, mult(ray.direction, 0.1));
		iterations++;
	}
	
	return (BLACK);
}