/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:37:59 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 13:38:30 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "vector.h"

#include <stdio.h>

void printVector(t_vec vec)
{
	printf("x: %f\ty: %f\tz: %f\n", vec.x, vec.y, vec.z);
}

float clamp(float value, float min, float max)
{
	if (value < min) return (min);
	else if (value > max) return (max);
	else return (value);
}