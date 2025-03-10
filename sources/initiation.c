/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:55:00 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/10 22:59:13 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "initiation.h"

#include <stdio.h>
#include <stdlib.h>

t_data	*initiateData(void)
{
	t_data	*data;

	printf("initiating...\n");
	data = malloc(sizeof(t_data));
	initiateMLX(&data->mlx_data);
	initiateScene(&data->scene_data);
	return (data);
}

void	initiateMLX(t_mlx_data *data)
{
	printf("initiating mlx...\n");
	data->width = WIDTH;
	data->height = HEIGHT;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "test");
	data->img = NULL;
	data->addr = NULL;
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