/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:48:45 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/12 23:33:28 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTING_H
#define INTERSECTING_H

#include "minirt.h"
#include "vector.h"
#include "rendering.h"

int intersectingSphere(t_vec point, t_sphere sphere);
int intersectingPlane(t_vec point, t_plane plane);
t_hit intersectingCylinder(t_vec point, t_cylinder cylinder);
float closestSphere(t_vec point, t_scene_data scene);
float closestCylinder(t_vec point, t_scene_data scene);
float closestShape(t_vec point, t_scene_data scene);

#endif