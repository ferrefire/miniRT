/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 21:30:45 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/13 16:46:09 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shapes.h"
#include "parsing.h"
#include "libft.h"
#include "utilities.h"
#include "vector.h"

#include <math.h>
#include <stdio.h>

void	parse_shape(char **tokens, t_shapes *shapes)
{
	if (ft_strncmp(tokens[0], "cy", ft_strlen("cy")) == 0)
	{
		parse_cylinder(tokens, shapes);
		shapes->cylinder_count++;
	}
	else if (ft_strncmp(tokens[0], "sp", ft_strlen("sp")) == 0)
	{
		parse_sphere(tokens, shapes);
		shapes->sphere_count++;
	}
	else if (ft_strncmp(tokens[0], "pl", ft_strlen("pl")) == 0)
	{
		parse_plane(tokens, shapes);
		shapes->plane_count++;
	}
}
