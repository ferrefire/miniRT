/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initiation.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:55:00 by ferre         #+#    #+#                 */
/*   Updated: 2025/02/19 18:35:59 by ferre         ########   odam.nl         */
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
	return (data);
}

void	initiateMLX(t_mlx_data *data)
{
	printf("initiating mlx...\n");
	data->width = 400;
	data->height = 400;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->width, data->height, "test");
	data->img = NULL;
	data->addr = NULL;
}