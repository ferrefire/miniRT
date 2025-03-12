/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:26:12 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 15:04:13 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "vector.h"
#include "scene.h"
#include "shapes.h"

#define WIDTH 10
#define HEIGHT 10

typedef struct s_mlx_data
{
	void *mlx;	// stores pointer returned by mlx init
	void *win;	// stores pointer to window
	//void *img;	// stores point created by mlx_new_image
	int width;
	int height;
} t_mlx_data;

typedef struct s_data
{
	t_mlx_data mlx_data;
	t_scene_data scene_data;
} t_data;

#endif
