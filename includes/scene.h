/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:32:44 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 14:42:34 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
#define SCENE_H

#include "vector.h"

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

void parse_ambient(char **tokens, t_scene_data *scene);
void parse_camera(char **tokens, t_scene_data *scene);
void parse_light(char **tokens, t_scene_data *scene);

#endif