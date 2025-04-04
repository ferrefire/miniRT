/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:26:28 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 16:45:15 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec
{
	float	x;
	float	y;
	float	z;
}	t_vec;

float	length(t_vec vec);
t_vec	normalize(t_vec vec);
t_vec	cross(t_vec a, t_vec b);
t_vec	add(t_vec a, t_vec b);
t_vec	sub(t_vec a, t_vec b);
t_vec	mult(t_vec a, float b);
float	dist(t_vec a, t_vec b);
float	distance_sq(t_vec a, t_vec b);
float	dot(t_vec a, t_vec b);
t_vec	lerp(t_vec a, t_vec b, float x);
t_vec	clamp_vec(t_vec a, float min, float max);

#endif
