/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaning.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:59:01 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 14:56:33 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "cleaning.h"

#include <stdlib.h>
#include <stdio.h>

void	cleanData(t_data *data)
{
	printf("cleaning...\n");
	cleanMLX(&data->mlx_data);
	clear(&data);
}

void	cleanMLX(t_mlx_data *data)
{
	printf("cleaning mlx...\n");
	if (data->mlx)
	{
		if (data->win)
		{
			mlx_clear_window(data->mlx, data->win);
			mlx_destroy_window(data->mlx, data->win);
		}
		mlx_destroy_display(data->mlx);
		clear(&data->mlx);
	}
}

void	clear(void *address)
{
	void	**memory;

	memory = (void **)address;
	if (memory != NULL)
	{
		if (*memory != NULL)
		{
			free(*memory);
		}
		*memory = NULL;
	}
}

void free_tokens(char **tokens)
{
	int i;

	i = 0;
	if (!tokens)
		return;
	while (tokens[i] != NULL)
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}