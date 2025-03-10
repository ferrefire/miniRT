/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:20:55 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/10 21:11:16 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
#define RENDERING_H

#include "minirt.h"

#define WHITE (t_rgb){255, 255, 255}
#define RED (t_rgb){255, 0, 0}
#define GREEN (t_rgb){0, 255, 0}
#define BLUE (t_rgb){0, 0, 255}

int colorToInt(t_rgb color);
void renderPixel(int x, int y, t_rgb color, t_data *data);
void renderImage(t_data *data);

#endif