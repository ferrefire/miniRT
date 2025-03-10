/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:26:28 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/10 21:30:37 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
#define VECTOR_H

typedef struct s_vec
{
	float x;
	float y;
	float z;
} t_vec;

float length(t_vec vec);
t_vec normalize(t_vec vec);

#endif