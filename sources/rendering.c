/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:18:41 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/12 16:50:47 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "rendering.h"
#include "intersecting.h"
#include "ray.h"
#include "utilities.h"

#include <stdio.h>

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
	printf("image rendered!\n");
	mlx_loop(data->mlx_data.mlx);
}

t_vec traceRay(t_ray ray, t_scene_data scene)
{
	t_hit hitInfo;
	int iterations;

	iterations = 0;
	while (iterations < 500)
	{
		hitInfo = checkIntersections(ray, scene);
		if (hitInfo.intersected)
		{
			t_vec lightNormal = normalize(sub(scene.light.source, ray.position));
			float shadow = inShadow((t_ray){ray.position, lightNormal}, scene);
			float lightDistance = 1.0 - clamp(distance(ray.position, scene.light.source) / 200.0, 0.0, 1.0);
			float diffuse = clamp(dot(hitInfo.normal, lightNormal) * lightDistance * shadow, scene.ambient.intensity, 1.0);
			return (mult(hitInfo.color, diffuse));
		}
		ray.position = add(ray.position, mult(ray.direction, 0.1));
		iterations++;
	}
	
	return (BLACK);
}

float inShadow(t_ray ray, t_scene_data scene)
{
	t_hit hitInfo;
	int iterations;

	iterations = 0;
	ray.position = add(ray.position, mult(ray.direction, 0.5));
	while (iterations < 100)
	{
		if (distance(ray.position, scene.light.source) <= 1.0)
			break;
		hitInfo = checkIntersections(ray, scene);
		if (hitInfo.intersected)
			return (0.0);
		ray.position = add(ray.position, mult(ray.direction, 0.25));
		iterations++;
	}

	return (1.0);
}

t_hit checkIntersections(t_ray ray, t_scene_data scene)
{
	t_hit hitInfo;
	int i;

	i = 0;
	while (i < scene.shapes.planeCount)
	{
		if (intersectingPlane(ray.position, scene.shapes.planes[i]))
		{
			hitInfo.intersected = 1;
			hitInfo.color = scene.shapes.planes[i].color;
			hitInfo.normal = scene.shapes.planes[i].normal;
			return (hitInfo);
		}
		i++;
	}
	i = 0;
	while (i < scene.shapes.sphereCount)
	{
		if (intersectingSphere(ray.position, scene.shapes.spheres[i]))
		{
			hitInfo.intersected = 1;
			hitInfo.color = scene.shapes.spheres[i].color;
			hitInfo.normal = normalize(sub(ray.position, scene.shapes.spheres[i].center));
			return (hitInfo);
		}
		i++;
	}
	hitInfo.intersected = 0;
	return (hitInfo);
}