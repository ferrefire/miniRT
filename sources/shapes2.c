/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:30:45 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 16:46:09 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shapes.h"
#include "parsing.h"
#include "libft.h"
#include "utilities.h"
#include "vector.h"

#include <math.h>
#include <stdio.h>

void	parse_shape(char **tokens, t_shapes *shapes)
{
	if (ft_strncmp(tokens[0], "cy", ft_strlen("cy")) == 0)
	{
		parse_cylinder(tokens, shapes);
		shapes->cylinder_count++;
	}
	else if (ft_strncmp(tokens[0], "sp", ft_strlen("sp")) == 0)
	{
		parse_sphere(tokens, shapes);
		shapes->sphere_count++;
	}
	else if (ft_strncmp(tokens[0], "pl", ft_strlen("pl")) == 0)
	{
		parse_plane(tokens, shapes);
		shapes->plane_count++;
	}
}

void	parse_cylinder(char **tokens, t_shapes *shapes)
{
	int			token_count;
	t_cylinder	*cylinder;
	float		length;

	token_count = 0;
	while (tokens[token_count])
		token_count++;
	if (token_count != 6)
	{
		printf("Error: Cylinder definition requires 5 parameters\n");
		exit(1);
	}
	if (shapes->cylinders == NULL)
		shapes->cylinders = (t_cylinder *)malloc(sizeof(t_cylinder));
	else
		shapes->cylinders = (t_cylinder *)memory_realloc(shapes->cylinders,
				sizeof(t_cylinder) * shapes->cylinder_count,
				sizeof(t_cylinder) * (shapes->cylinder_count + 1));
	if (!shapes->cylinders)
	{
		printf("Error: Memory allocation failed for cylinder\n");
		exit(1);
	}
	cylinder = &shapes->cylinders[shapes->cylinder_count];
	parse_cylinder2(cylinder, length, tokens);
}

void	parse_cylinder2(t_cylinder *cylinder, float length, char **tokens)
{
	cylinder->position = parse_vec(tokens[1]);
	cylinder->axis = normalize(parse_vec(tokens[2]));
	cylinder->radius = atof(tokens[3]) * 0.5;
	cylinder->h = atof(tokens[4]);
	cylinder->color = parse_vec(tokens[5]);
	cylinder->type = 3;
	length = sqrt(cylinder->axis.x * cylinder->axis.x
			+ cylinder->axis.y * cylinder->axis.y
			+ cylinder->axis.z * cylinder->axis.z);
	if (length == 0)
	{
		printf("Error: Cylinder axis vector cannot be zero\n");
		exit(1);
	}
	cylinder->axis.x /= length;
	cylinder->axis.y /= length;
	cylinder->axis.z /= length;
	if (cylinder->radius <= 0 || cylinder->h <= 0)
	{
		printf("Error: Cylinder diameter and height must be positive\n");
		exit(1);
	}
}
