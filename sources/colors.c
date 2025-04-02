/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:20:55 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 16:09:07 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"

t_vec	fwhite(void)
{
	t_vec	color;

	color.x = 255.0;
	color.y = 255.0;
	color.z = 255.0;
	return (color);
}

t_vec	fblack(void)
{
	t_vec	color;

	color.x = 0.0;
	color.y = 0.0;
	color.z = 0.0;
	return (color);
}

t_vec	fred(void)
{
	t_vec	color;

	color.x = 255.0;
	color.y = 0.0;
	color.z = 0.0;
	return (color);
}

t_vec	fgreen(void)
{
	t_vec	color;

	color.x = 0.0;
	color.y = 255.0;
	color.z = 0.0;
	return (color);
}

t_vec	fblue(void)
{
	t_vec	color;

	color.x = 0.0;
	color.y = 0.0;
	color.z = 255.0;
	return (color);
}
