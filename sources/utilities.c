/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:37:59 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/10 21:42:04 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "utilities.h"
#include "vector.h"

#include <stdio.h>

void printVector(t_vec vec)
{
	printf("x: %f\ty: %f\tz: %f\n", vec.x, vec.y, vec.z);
}