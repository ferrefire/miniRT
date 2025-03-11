/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilities.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:37:01 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/11 13:37:40 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_H
#define UTILITIES_H

#include "vector.h"

void printVector(t_vec vec);
float clamp(float value, float min, float max);

#endif