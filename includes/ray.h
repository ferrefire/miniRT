/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:25:15 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 15:33:14 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"
# include "vector.h"

typedef struct s_ray
{
	t_vec	pos;
	t_vec	direction;
	t_vec	origin;
	t_vec	target;
	float	max;
}	t_ray;

t_ray	initiate_ray(int x, int y, t_camera camera);

#endif
