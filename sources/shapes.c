/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:42:55 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/12 21:26:22 by ferre         ########   odam.nl         */
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

int	invalid_shape(void)
{
	printf("Error: shape defintion invalid.");
	return (1);
}

int	mem_error(void)
{
	printf("Error: memory alloc error");
	return (1);
}

void	parse_sphere(char **tokens, t_shapes *shapes)
{
	int			token_count;
	t_sphere	*sphere;

	token_count = 0;
	while (tokens[token_count])
		token_count++;
	if (token_count != 4)
		exit(invalid_shape());
	if (shapes->spheres == NULL)
		shapes->spheres = (t_sphere *)malloc(sizeof(t_sphere));
	else
		shapes->spheres = (t_sphere *)memory_realloc(shapes->spheres,
				sizeof(t_sphere) * shapes->sphere_count,
				sizeof(t_sphere) * (shapes->sphere_count + 1));
	if (!shapes->spheres)
		exit(mem_error());
	sphere = &shapes->spheres[shapes->sphere_count];
	sphere->type = 1;
	sphere->center = parse_vec(tokens[1]);
	sphere->radius = ft_atof(tokens[2]) * 0.5;
	sphere->color = parse_vec(tokens[3]);
	if (sphere->radius <= 0)
		exit(invalid_shape());
}

void	parse_plane(char **tokens, t_shapes *shapes)
{
	int			token_count;
	t_plane		*plane;
	float		length;

	token_count = 0;
	while (tokens[token_count])
		token_count++;
	if (token_count != 4)
		exit(invalid_shape());
	if (shapes->planes == NULL)
		shapes->planes = (t_plane *)malloc(sizeof(t_plane));
	else
		shapes->planes = (t_plane *)memory_realloc(shapes->planes,
				sizeof(t_plane) * shapes->plane_count,
				sizeof(t_plane) * (shapes->plane_count + 1));
	if (!shapes->planes)
		exit(mem_error());
	plane = &shapes->planes[shapes->plane_count];
	plane->type = 2;
	plane->position = parse_vec(tokens[1]);
	plane->normal = parse_vec(tokens[2]);
	plane->color = parse_vec(tokens[3]);
	parse_plane2(plane, length);
}

void	parse_plane2(t_plane *plane, float length)
{
	length = sqrt(plane->normal.x * plane->normal.x
			+ plane->normal.y * plane->normal.y
			+ plane->normal.z * plane->normal.z);
	if (length == 0)
		exit(invalid_shape());
	plane->normal.x /= length;
	plane->normal.y /= length;
	plane->normal.z /= length;
}
