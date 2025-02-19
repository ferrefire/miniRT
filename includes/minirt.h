/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minirt.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/02/19 17:26:12 by ferre         #+#    #+#                 */
/*   Updated: 2025/02/19 17:47:41 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

typedef struct s_mlx_data
{
	void *mlx;	// stores pointer returned by mlx init
	void *win;	// stores pointer to window
	void *img;	// stores point created by mlx_new_image
	char *addr; //
	int bpp;	// Bits per pixel
	int line_length;
	int endian; // probably not necessary
	int width;
	int height;
} t_mlx_data;

typedef struct s_xyz
{
	float x;
	float y;
	float z;
} t_xyz;

typedef struct s_rgb
{
	int r;
	int g;
	int b;
} t_rgb;

typedef struct s_ambient
{
	float intensity;
	t_rgb colour;
} t_ambient;

typedef struct s_camera
{
	t_xyz position;
	t_xyz orientation;
	float fov;
} t_camera;

typedef struct s_light
{
	float intensity;
	t_rgb colour;
	t_xyz source;
} t_light;

typedef struct s_scene_data
{
	t_ambient ambient;
	t_camera camera;
	t_light light;
	// SHAPES + NUM OF SHAPES
} t_scene_data;

typedef struct s_data
{
	t_mlx_data mlx_data;
	t_scene_data scene_data;
} t_data;

#endif