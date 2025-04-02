/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:34:32 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/12 21:34:55 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include "parsing.h"

#include <stdlib.h> // For malloc, free, exit
#include <stdio.h>

void	parse_ambient(char **tokens, t_scene_data *scene)
{
	if (!tokens[1] || !tokens[2])
	{
		printf("Error parsing token");
		exit(EXIT_FAILURE);
	}
	scene->ambient.intensity = atof(tokens[1]);
	scene->ambient.color = parse_vec(tokens[2]);
}

void	parse_camera(char **tokens, t_scene_data *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3] || scene->has_cam == 1)
	{
		printf("Error parsing camera token");
		exit(EXIT_FAILURE);
	}
	scene->camera.position = parse_vec(tokens[1]);
	scene->camera.foward = normalize(parse_vec(tokens[2]));
	scene->camera.fov = atof(tokens[3]);
	scene->has_cam = 1;
}

void	parse_light(char **tokens, t_scene_data *scene)
{
	if (!tokens[1] || !tokens[2] || !tokens[3])
	{
		printf("Error parsing L Token");
		exit(EXIT_FAILURE);
	}
	scene->light.src = parse_vec(tokens[1]);
	scene->light.intensity = atof(tokens[2]);
	scene->light.color = parse_vec(tokens[3]);
}
