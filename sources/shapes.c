/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:42:55 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 14:53:40 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shapes.h"
#include "parsing.h"
#include "libft.h"

#include "math.h"

void parse_sphere(char **tokens, t_shapes *shapes)
{
	int token_count;
	t_sphere *sphere;

	token_count = 0;
	while (tokens[token_count])
		token_count++;

	if (token_count != 4)
	{
		printf("Error: sphere definition invalid");
		exit(1);
	}

	if (shapes->spheres == NULL)
		shapes->spheres = (t_sphere *)malloc(sizeof(t_sphere));
	else
		shapes->spheres = (t_sphere *)realloc(shapes->spheres, sizeof(t_sphere) * (shapes->sphereCount + 1));

	if (!shapes->spheres)
	{
		printf("Memory Error: parse_sphere");
		exit(1);
	}

	sphere = &shapes->spheres[shapes->sphereCount];
	sphere->type = 1;
	sphere->center = parse_vec(tokens[1]);
	sphere->radius = ft_atof(tokens[2]);
	sphere->color = parse_vec(tokens[3]);

	if (sphere->radius <= 0)
	{
		printf("Error: sphere definition invalid");
		exit(1);
	}
}

void parse_plane(char **tokens, t_shapes *shapes)
{
	int token_count;
	t_plane *plane;
	float length;

	token_count = 0;
	while (tokens[token_count])
		token_count++;

	if (token_count != 4)
	{
		printf("Error: Plane definition requires 3 parameters\n");
		exit(1);
	}

	if (shapes->planes == NULL)
		shapes->planes = (t_plane *)malloc(sizeof(t_plane));
	else
		shapes->planes = (t_plane *)realloc(shapes->planes,
										   sizeof(t_plane) * (shapes->planeCount + 1));

	if (!shapes->planes)
	{
		printf("Error: Memory allocation failed for plane\n");
		exit(1);
	}

	plane = &shapes->planes[shapes->planeCount];
	plane->type = 2;
	plane->position = parse_vec(tokens[1]);
	plane->normal = parse_vec(tokens[2]);
	plane->color = parse_vec(tokens[3]);

	length = sqrt(plane->normal.x * plane->normal.x +
				  plane->normal.y * plane->normal.y +
				  plane->normal.z * plane->normal.z);

	if (length == 0)
	{
		printf("Error: Plane normal vector cannot be zero\n");
		exit(1);
	}

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
		shapes->cylinders = (t_cylinder *)realloc(shapes->cylinders,
												 sizeof(t_cylinder) * (shapes->cylinderCount + 1));

	if (!shapes->cylinders)
	{
		printf("Error: Memory allocation failed for cylinder\n");
		exit(1);
	}

	cylinder = &shapes->cylinders[shapes->cylinderCount];
	cylinder->type = 3; // Type identifier for cylinder
	cylinder->position = parse_vec(tokens[1]);
	cylinder->axis = parse_vec(tokens[2]);
	cylinder->radius = ft_atof(tokens[3]);
	cylinder->height = ft_atof(tokens[4]);
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

void parse_cone(char **tokens, t_shapes *shapes)
{
	int token_count;
	t_cone *cone;
	float length;

	token_count = 0;
	while (tokens[token_count])
		token_count++;

	if (token_count != 6)
	{
		printf("Error: Cone definition requires 5 parameters\n");
		exit(1);
	}

	if (shapes->cones == NULL)
		shapes->cones = (t_cone *)malloc(sizeof(t_cone));
	else
		shapes->cones = (t_cone *)realloc(shapes->cones,
										 sizeof(t_cone) * (shapes->coneCount + 1));

	if (!shapes->cones)
	{
		printf("Error: Memory allocation failed for cone\n");
		exit(1);
	}

	cone = &shapes->cones[shapes->coneCount];
	cone->type = 4;
	cone->vertex = parse_vec(tokens[1]);
	cone->axis = parse_vec(tokens[2]);
	cone->angle = ft_atof(tokens[3]);
	cone->height = ft_atof(tokens[4]);
	cone->color = parse_vec(tokens[5]);

	length = sqrt(cone->axis.x * cone->axis.x +
				  cone->axis.y * cone->axis.y +
				  cone->axis.z * cone->axis.z);

	if (length == 0)
	{
		printf("Error: Cone axis vector cannot be zero\n");
		exit(1);
	}

	cone->axis.x /= length;
	cone->axis.y /= length;
	cone->axis.z /= length;

	if (cone->angle <= 0 || cone->angle >= 90 || cone->height <= 0)
	{
		printf("Error: Cone angle must be between 0 and 90, and height must be positive\n");
		exit(1);
	}
	// Convert angle from degrees to radians
	cone->angle = cone->angle * PI / 180.0;
}

void parse_triangle(char **tokens, t_shapes *shapes)
{
	int token_count;
	t_triangle *triangle;

	token_count = 0;
	while (tokens[token_count])
		token_count++;

	if (token_count != 5)
	{
		printf("Error: Triangle definition requires 4 parameters\n");
		exit(1);
	}

	if (shapes->triangles == NULL)
		shapes->triangles = (t_triangle *)malloc(sizeof(t_triangle));
	else
		shapes->triangles = (t_triangle *)realloc(shapes->triangles,
												 sizeof(t_triangle) * (shapes->triangleCount + 1));

	if (!shapes->triangles)
	{
		printf("Error: Memory allocation failed for triangle\n");
		exit(1);
	}

	triangle = &shapes->triangles[shapes->triangleCount];
	triangle->type = 5; // Type identifier for triangle
	triangle->v1 = parse_vec(tokens[1]);
	triangle->v2 = parse_vec(tokens[2]);
	triangle->v3 = parse_vec(tokens[3]);
	triangle->color = parse_vec(tokens[4]);
}

void parse_disc(char **tokens, t_shapes *shapes)
{
	int token_count;
	t_disc *disc;
	float length;

	token_count = 0;
	while (tokens[token_count])
		token_count++;

	if (token_count != 5)
	{
		printf("Error: Disc definition requires 4 parameters\n");
		exit(1);
	}

	if (shapes->discs == NULL)
		shapes->discs = (t_disc *)malloc(sizeof(t_disc));
	else
		shapes->discs = (t_disc *)realloc(shapes->discs,
										 sizeof(t_disc) * (shapes->discCount + 1));

	if (!shapes->discs)
	{
		printf("Error: Memory allocation failed for disc\n");
		exit(1);
	}

	disc = &shapes->discs[shapes->discCount];
	disc->type = 6;
	disc->center = parse_vec(tokens[1]);
	disc->normal = parse_vec(tokens[2]);
	disc->radius = ft_atof(tokens[3]);
	disc->color = parse_vec(tokens[4]);

	length = sqrt(disc->normal.x * disc->normal.x +
				  disc->normal.y * disc->normal.y +
				  disc->normal.z * disc->normal.z);

	if (length == 0)
	{
		printf("Error: Disc normal vector cannot be zero\n");
		exit(1);
	}

	disc->normal.x /= length;
	disc->normal.y /= length;
	disc->normal.z /= length;

	if (disc->radius <= 0)
	{
		printf("Error: Disc radius must be positive\n");
		exit(1);
	}
}

void parse_shape(char **tokens, t_shapes *shapes)
{
	if (ft_strncmp(tokens[0], "cy", ft_strlen("cy") + 1) == 0)
	{
		parse_cylinder(tokens, shapes);
		shapes->cylinderCount++;
	}
	else if (ft_strncmp(tokens[0], "sp", ft_strlen("sp") + 1) == 0)
	{
		parse_sphere(tokens, shapes);
		shapes->sphereCount++;
	}
	else if (ft_strncmp(tokens[0], "pl", ft_strlen("pl") + 1) == 0)
	{
		parse_plane(tokens, shapes);
		shapes->planeCount++;
	}
	else if (ft_strncmp(tokens[0], "co", ft_strlen("co") + 1) == 0)
	{
		parse_cone(tokens, shapes);
		shapes->coneCount++;
	}
	else if (ft_strncmp(tokens[0], "tr", ft_strlen("tr") + 1) == 0)
	{
		parse_triangle(tokens, shapes);
		shapes->triangleCount++;
	}
	else if (ft_strncmp(tokens[0], "di", ft_strlen("di") + 1) == 0)
	{
		parse_disc(tokens, shapes);
		shapes->discCount++;
	}
}