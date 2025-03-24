/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:02:36 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/12 22:55:36 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "minirt.h"
# include "vector.h"

# define PI 3.141592654

typedef struct s_sphere
{
	int		type;
	t_vec	color;
	t_vec	center;
	float	radius;
	float	radius_squared;
}	t_sphere;

typedef struct s_plane
{
	int		type;
	t_vec	color;
	t_vec	position;
	t_vec	normal;
}	t_plane;

typedef struct s_cylinder
{
	int		type;
	t_vec	color;
	t_vec	position;
	t_vec	axis;
	float	radius;
	float	h;
}	t_cylinder;

typedef struct s_cone
{
	int		type;
	t_vec	color;
	t_vec	vertex;
	t_vec	axis;
	float	angle;
	float	height;
}	t_cone;

typedef struct s_triangle
{
	int		type;
	t_vec	color;
	t_vec	v1;
	t_vec	v2;
	t_vec	v3;
}	t_triangle;

typedef struct s_disc
{
	int		type;
	t_vec	color;
	t_vec	center;
	t_vec	normal;
	float	radius;
}	t_disc;

typedef struct s_shapes
{
	t_sphere	*spheres;
	int			sphere_count;
	t_plane		*planes;
	int			plane_count;
	t_cylinder	*cylinders;
	int			cylinder_count;
	t_cone		*cones;
	int			cone_count;
	t_triangle	*triangles;
	int			triangle_count;
	t_disc		*discs;
	int			disc_count;
}	t_shapes;

void	parse_sphere(char **tokens, t_shapes *shapes);
void	parse_plane(char **tokens, t_shapes *shapes);
void	parse_plane2(t_plane *plane, float length);
void	parse_cylinder(char **tokens, t_shapes *shapes);
void	parse_cylinder2(t_cylinder *cylinder, float length, char **tokens);
void	parse_cone(char **tokens, t_shapes *shapes);
void	parse_triangle(char **tokens, t_shapes *shapes);
void	parse_disc(char **tokens, t_shapes *shapes);
void	parse_shape(char **tokens, t_shapes *shapes);

#endif
