/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:55:00 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 19:46:31 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "initiation.h"
#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>

t_data	*initiate_data(void)
{
	t_data	*data;

	printf("initiating...\n");
	data = malloc(sizeof(t_data));
	data->start = time(NULL);
	data->x = 0;
	data->y = 0;
	initiate_scene(&data->scene_data);
	initiate_mlx(&data->mlx_data);
	return (data);
}

void	initiate_mlx(t_mlx_data *data)
{
	printf("initiating mlx...\n");
	data->mlx = NULL;
	data->win = NULL;
	data->image_data.image = NULL;
	data->image_data.address = NULL;
	data->width = WIDTH;
	data->height = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "test");
	data->image_data.image = mlx_new_image(data->mlx,
			data->width, data->height);
	data->image_data.address = mlx_get_data_addr(data->image_data.image,
			&data->image_data.bpp, &data->image_data.line,
			&data->image_data.endian);
}

void	initiate_scene(t_scene_data *data)
{
	printf("initiating scene...\n");
	data->camera.position = (t_vec){0, 0, 0};
	data->camera.foward = (t_vec){0, 0, 1};
	data->camera.right = normalize(cross(
				data->camera.foward, (t_vec){0, 1, 0}));
	data->camera.up = normalize(cross(data->camera.right, data->camera.foward));
	data->camera.fov = 45;
	data->camera.aspect_ratio = (float)WIDTH / (float)HEIGHT;
	data->ambient.color = (t_vec){255, 255, 255};
	data->ambient.intensity = 0.1;
	data->light.color = (t_vec){255, 255, 255};
	data->light.intensity = 1.0;
	data->light.src = normalize((t_vec){1, 1, -1});
	data->shapes.spheres = NULL;
	data->shapes.sphere_count = 0;
	data->shapes.planes = NULL;
	data->shapes.plane_count = 0;
	data->shapes.cylinders = NULL;
	data->shapes.cylinder_count = 0;
	data->step = 0.005;
	data->camera.far = 50.0;
	data->has_cam = 0;
}
