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

int colorToInt(t_vec color)
{
	return (255 << 24 | (int)color.x << 16 | (int)color.y << 8 | (int)color.z);
}

void renderPixel(int x, int y, t_vec color, t_data *data)
{
	char *dst;

	//mlx_pixel_put(data->mlx_data.mlx, data->mlx_data.win, x, y, colorToInt(color));

	dst = data->mlx_data.image_data.address + (y * data->mlx_data.image_data.line + x * (data->mlx_data.image_data.bpp / 8));
	*(unsigned int *)dst = colorToInt(color);

	//mlx_put_image_to_window(data->mlx_data.mlx, data->mlx_data.win, data->mlx_data.image_data.image, 0, 0);
}

int renderImage(t_data *data)
{
	if (data->y >= HEIGHT) return (1);

	t_ray currentRay = initiateRay(data->x, data->y, data->scene_data.camera);
	t_vec pixelColor = traceRay(currentRay, data->scene_data);
	renderPixel(data->x, data->y, pixelColor, data);

	data->x += 1;

	if (data->x >= WIDTH)
	{
		data->x = 0;
		data->y += 1;
		if (data->y >= HEIGHT)
		{
			//mlx_put_image_to_window(data->mlx_data.mlx, data->mlx_data.win, data->mlx_data.image_data.image, 0, 0);
			printf("image rendered in %ld seconds\n", (time(NULL) - data->start));
		}
		mlx_put_image_to_window(data->mlx_data.mlx, data->mlx_data.win, data->mlx_data.image_data.image, 0, 0);
	}

	return (0);
}

t_vec traceRay(t_ray ray, t_scene_data scene)
{
	t_hit hitInfo;
	//float inter;

	//inter = 0.0;
	//while (inter <= 1.0)
	while (distanceSquared(ray.position, ray.origin) < scene.camera.far * scene.camera.far)
	{
		hitInfo = checkIntersections(ray, scene);
		if (hitInfo.intersected)
		{
			t_vec lightNormal = normalize(sub(scene.light.source, ray.position));
			float shadow = inShadow((t_ray){ray.position, lightNormal, ray.position, scene.light.source, 
				distance(ray.position, scene.light.source)}, scene);
			// float shadow = inShadow((t_ray){ray.position, lightNormal, ray.position, scene.light.source}, scene);
			//float shadow = 1.0;
			float lightDistance = 1.0;
			float diffuse = clamp(dot(hitInfo.normal, lightNormal) * lightDistance * shadow, scene.ambient.intensity, 1.0);
			t_vec specularColor = BLACK;
			//if (shadow > 0.0)
			{
				t_vec reflectionNormal = sub(mult(hitInfo.normal, 2.0 * dot(lightNormal, hitInfo.normal)), lightNormal);
				float specular = clamp(dot(mult(ray.direction, -1.0), reflectionNormal), 0.0, 1.0);
				specular = pow(specular, 4.0);
				specularColor = mult(WHITE, specular);
			}
			return (clampVec(mult(add(hitInfo.color, specularColor), diffuse), 0.0, 255.0));
		}
		// float closest = closestShape(ray.position, scene);
		// inter += scene.step * clamp(closest, 1.0, 100.0);
		// ray.position = lerp(ray.origin, ray.target, inter);
		// float closest = clamp(closestShape(ray.position, scene), scene.step, scene.camera.far);
		float closest = clamp(hitInfo.distance, scene.step, scene.camera.far);
		ray.position = add(ray.position, mult(ray.direction, closest));
	}

	return (BLACK);
}

float inShadow(t_ray ray, t_scene_data scene)
{
	t_hit hitInfo;
	int away = 0;
	//float inter;

	//inter = scene.step * 25.0;
	//ray.position = lerp(ray.origin, ray.target, inter);
	//while (inter <= 1.0)
	ray.position = add(ray.position, mult(ray.direction, 0.1));
	while (distanceSquared(ray.position, ray.origin) < ray.max * ray.max)
	{
		hitInfo = checkIntersections(ray, scene);
		if (hitInfo.intersected)
			return (0.0);
		//if (away && hitInfo.intersected)
		//	return (0.0);
		//if (!away && !hitInfo.intersected)
		//	away = 1;
		//float closest = closestShape(ray.position, scene);
		//inter += (scene.step * 5.0) * clamp(closest, 1.0, 100.0);
		//ray.position = lerp(ray.origin, ray.target, inter);
		//float closest = clamp(closestShape(ray.position, scene), scene.step, ray.max);
		float closest = clamp(hitInfo.distance, scene.step, ray.max);
		ray.position = add(ray.position, mult(ray.direction, closest));
	}

	return (1.0);
}

/*void renderImage(t_data *data)
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
}*/

/*t_vec traceRay(t_ray ray, t_scene_data scene)
{
	t_hit hitInfo;
	int iterations;

	iterations = 0;
	while (iterations < 1000)
	{
		hitInfo = checkIntersections(ray, scene);
		if (hitInfo.intersected)
		{
			t_vec lightNormal = normalize(sub(scene.light.source, ray.position));
			//float shadow = inShadow((t_ray){ray.position, lightNormal}, scene);
			float shadow = 1;
			//float lightDistance = 1.0 - clamp(distance(ray.position, scene.light.source) / 75.0, 0.0, 1.0);
			//lightDistance *= lightDistance;
			//lightDistance *= lightDistance;
			float lightDistance = 1.0;
			float diffuse = clamp(dot(hitInfo.normal, lightNormal) * lightDistance * shadow, scene.ambient.intensity, 1.0);
			return (mult(hitInfo.color, diffuse));
		}
		ray.position = add(ray.position, mult(ray.direction, 0.05));
		iterations++;
	}
	
	return (BLACK);
}*/

/*float inShadow(t_ray ray, t_scene_data scene)
{
	t_hit hitInfo;
	int iterations;

	iterations = 0;
	ray.position = add(ray.position, mult(ray.direction, 0.5));
	while (iterations < 500)
	{
		if (distance(ray.position, scene.light.source) <= 1.0)
			break;
		hitInfo = checkIntersections(ray, scene);
		if (hitInfo.intersected)
			return (0.0);
		ray.position = add(ray.position, mult(ray.direction, 0.1));
		iterations++;
	}

	return (1.0);
}*/

t_hit checkIntersections(t_ray ray, t_scene_data scene)
{
	t_hit hitInfo;
	float closest;
	int i;

	closest = 10000.0;
	i = 0;
	while (i < scene.shapes.planeCount)
	{
		hitInfo = intersectingPlane(ray.position, scene.shapes.planes[i]);
		if (hitInfo.intersected)
			return (hitInfo);
		if (hitInfo.distance < closest)
			closest = hitInfo.distance;
		i++;
	}

	i = 0;
	while (i < scene.shapes.sphereCount)
	{
		hitInfo = intersectingSphere(ray.position, scene.shapes.spheres[i]);
		if (hitInfo.intersected)
			return (hitInfo);
		if (hitInfo.distance < closest)
			closest = hitInfo.distance;
		i++;
	}

	i = 0;
	while (i < scene.shapes.cylinderCount)
	{
		hitInfo = intersectingCylinder(ray.position, scene.shapes.cylinders[i]);
		if (hitInfo.intersected)
			return (hitInfo);
		if (hitInfo.distance < closest)
			closest = hitInfo.distance;
		i++;
	}
	hitInfo.intersected = 0;
	hitInfo.distance = closest;
	return (hitInfo);
}