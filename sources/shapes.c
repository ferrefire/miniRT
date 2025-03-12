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

int  invalid_shape(void)
{
  printf("Error: shape defintion invalid.");
  return(1);
}

int   mem_error(void)
{
  printf("Error: memory alloc error");
  return (1);
}

void parse_sphere(char **tokens, t_shapes *shapes)
{
	int       token_count;
	t_sphere  *sphere;

	token_count = 0;
  while (tokens[token_count])
		token_count++;

	if (token_count != 4)
		exit(invalid_shape());

  if (shapes->spheres == NULL)
    shapes->spheres = (t_sphere *)malloc(sizeof(t_sphere));
  else
    shapes->spheres = (t_sphere *)memory_realloc(shapes->spheres, 
                                              sizeof(t_sphere) * shapes->sphereCount, 
                                              sizeof(t_sphere) * (shapes->sphereCount + 1));

	if (!shapes->spheres)
    exit(mem_error());
	sphere = &shapes->spheres[shapes->sphereCount];
	sphere->type = 1;
	sphere->center = parse_vec(tokens[1]);
	sphere->radius = ft_atof(tokens[2]) * 0.5;
	sphere->color = parse_vec(tokens[3]);

	if (sphere->radius <= 0)
     exit(invalid_shape());
}

void parse_plane(char **tokens, t_shapes *shapes)
{
	int     token_count;
	t_plane *plane;
	float   length;

	token_count = 0;
	while (tokens[token_count])
		token_count++;

	if (token_count != 4)
    exit(invalid_shape());
	if (shapes->planes == NULL)
		shapes->planes = (t_plane *)malloc(sizeof(t_plane));
	else
		shapes->planes = (t_plane *)memory_realloc(shapes->planes,
                                              sizeof(t_plane) * shapes->planeCount,
										                          sizeof(t_plane) * (shapes->planeCount + 1));

	if (!shapes->planes)
    exit(mem_error());
	plane = &shapes->planes[shapes->planeCount];
	plane->type = 2;
	plane->position = parse_vec(tokens[1]);
	plane->normal = parse_vec(tokens[2]);
	plane->color = parse_vec(tokens[3]);

	length = sqrt(plane->normal.x * plane->normal.x + plane->normal.y * plane->normal.y + plane->normal.z * plane->normal.z);

	if (length == 0)
    exit(invalid_shape());
	plane->normal.x /= length;
	plane->normal.y /= length;
	plane->normal.z /= length;
}

void parse_cylinder(char **tokens, t_shapes *shapes)
{
	int token_count;
	t_cylinder *cylinder;
	float length;
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
                                                    sizeof(t_cylinder) * shapes->cylinderCount,
												                            sizeof(t_cylinder) * (shapes->cylinderCount + 1));

	if (!shapes->cylinders)
	{
		printf("Error: Memory allocation failed for cylinder\n");
		exit(1);
	}

	cylinder = &shapes->cylinders[shapes->cylinderCount];
	cylinder->type = 3; // Type identifier for cylinder
	cylinder->position = parse_vec(tokens[1]);
	cylinder->axis = normalize(parse_vec(tokens[2]));
	cylinder->radius = atof(tokens[3]) * 0.5;
	cylinder->height = atof(tokens[4]);
	cylinder->color = parse_vec(tokens[5]);

	length = sqrt(cylinder->axis.x * cylinder->axis.x +
				  cylinder->axis.y * cylinder->axis.y +
				  cylinder->axis.z * cylinder->axis.z);

	if (length == 0)
	{
		printf("Error: Cylinder axis vector cannot be zero\n");
		exit(1);
	}

	cylinder->axis.x /= length;
	cylinder->axis.y /= length;
	cylinder->axis.z /= length;

	if (cylinder->radius <= 0 || cylinder->height <= 0)
	{
		printf("Error: Cylinder diameter and height must be positive\n");
		exit(1);
	}
}

void parse_shape(char **tokens, t_shapes *shapes)
{
	if (ft_strncmp(tokens[0], "cy", ft_strlen("cy")) == 0)
	{
		parse_cylinder(tokens, shapes);
		shapes->cylinderCount++;
	}
	else if (ft_strncmp(tokens[0], "sp", ft_strlen("sp")) == 0)
	{
		parse_sphere(tokens, shapes);
		shapes->sphereCount++;
	}
	else if (ft_strncmp(tokens[0], "pl", ft_strlen("pl")) == 0)
	{
		parse_plane(tokens, shapes);
		shapes->planeCount++;
	}
}
