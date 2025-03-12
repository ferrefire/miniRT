/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:55:00 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/12 23:34:32 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "initiation.h"
#include "parsing.h"

#include <stdio.h>
#include <stdlib.h>

t_data	*initiateData(void)
{
	t_data	*data;

	printf("initiating...\n");
	data = malloc(sizeof(t_data));
	data->start = time(NULL);
	data->x = 0;
	data->y = 0;
	initiateScene(&data->scene_data);
	initiateMLX(&data->mlx_data);
	return (data);
}

void	initiateMLX(t_mlx_data *data)
{
	printf("initiating mlx...\n");
	data->width = WIDTH;
	data->height = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "test");
	//data->img = NULL;
	//data->addr = NULL;
}

void	initiateScene(t_scene_data *data)
{
	printf("initiating scene...\n");
	
	data->camera.position = (t_vec){0, 0, 0};
	data->camera.foward = (t_vec){0, 0, 1};
	data->camera.right = normalize(cross(data->camera.foward, (t_vec){0, 1, 0}));
	data->camera.up = normalize(cross(data->camera.right, data->camera.foward));
	data->camera.fov = 45;
	data->camera.aspectRatio = (float)WIDTH / (float)HEIGHT;
	data->ambient.color = (t_vec){255, 255, 255};
	data->ambient.intensity = 0.1;
	data->light.color = (t_vec){255, 255, 255};
	data->light.intensity = 1.0;
	data->light.source = normalize((t_vec){1, 1, -1});

	data->shapes.spheres = NULL;
	data->shapes.sphereCount = 0;
	data->shapes.planes = NULL;
	data->shapes.planeCount = 0;
	data->shapes.cylinders = NULL;
	data->shapes.cylinderCount = 0;

	data->step = 0.001;
	data->camera.far = 50.0;

    //parse_file("scenes/invalid/duplicate_camera.rt", data);

	//data->light.source = normalize((t_vec){1, 1, -1});
	//data->camera.fov = 45;
}

/*void	initiateRays(t_ray_data *data, t_camera camera)
{
	int x;
	int y;

	printf("initiating rays...\n");
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			data->rays[x][y] = initiateRay(x, y, camera);
			x++;
		}
		y++;
	}
	
}*/
