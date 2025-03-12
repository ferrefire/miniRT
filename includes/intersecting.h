/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersecting.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 22:48:45 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/12 15:55:13 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTING_H
#define INTERSECTING_H

#include "minirt.h"
#include "vector.h"

int intersectingSphere(t_vec point, t_sphere sphere);
int intersectingPlane(t_vec point, t_plane plane);

#endif