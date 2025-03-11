/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shapes.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/11 14:02:36 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 14:08:48 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
#define SHAPES_H

#include "minirt.h"
#include "vector.h"

typedef struct s_sphere
{
	int type; // 1 = for s_sphere
	t_vec color;
	t_vec center;
	float radius;
} t_sphere;

typedef struct s_plane
{
	int type; // 2 for s_plane
	t_vec color;
	t_vec position;
	t_vec normal;
} t_plane;

typedef struct s_cylinder
{
	int type; // 3 for s_cylinder
	t_vec color;
	t_vec position;
	t_vec axis;
	float radius;
	float height;
} t_cylinder;

typedef struct s_cone
{
	int type; // 4 for s_cone
	t_vec color;
	t_vec vertex;
	t_vec axis;
	float angle;
	float height;
} t_cone;

typedef struct s_triangle
{
	int type; // 5 for s_triangle
	t_vec color;
	t_vec v1;
	t_vec v2;
	t_vec v3;
} t_triangle;

typedef struct s_disc
{
	int type; // 6 for s_disc
	t_vec color;
	t_vec center;
	t_vec normal;
	float radius;
} t_disc;

typedef struct s_shapes
{
	t_sphere *spheres;
	int sphereCount;

	t_plane *planes;
	int planeCount;

	t_cylinder *cylinders;
	int cylinderCount;

	t_cone *cones;
	int coneCount;

	t_triangle *triangles;
	int triangleCount;

	t_disc *discs;
	int discCount;
} t_shapes;

#endif