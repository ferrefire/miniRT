/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:26:12 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 14:09:04 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "vector.h"
#include "shapes.h"

#define WIDTH 400
#define HEIGHT 400

typedef struct s_mlx_data
{
	void *mlx;	// stores pointer returned by mlx init
	void *win;	// stores pointer to window
	void *img;	// stores point created by mlx_new_image
	int width;
	int height;
} t_mlx_data;

typedef struct s_ambient
{
	float intensity;
	t_vec color;
} t_ambient;

typedef struct s_camera
{
	t_vec position;
	t_vec foward;
	t_vec up;
	t_vec right;
	float fov;
	float aspectRatio;
} t_camera;

typedef struct s_light
{
	float intensity;
	t_vec color;
	t_vec source;
} t_light;

typedef struct s_sphere
{
	t_vec color;
	t_vec center;
	float radius;
} t_sphere;

typedef struct s_scene_data
{
	t_ambient ambient;
	t_camera camera;
	t_light light;
	t_shapes shapes;
} t_scene_data;

typedef struct s_data
{
	t_mlx_data mlx_data;
	t_scene_data scene_data;
} t_data;

#endif