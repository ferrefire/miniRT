/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rendering.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: ferre <ferre@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 20:18:41 by ferre         #+#    #+#                 */
/*   Updated: 2025/03/10 21:14:17 by ferre         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "rendering.h"

int colorToInt(t_rgb color)
{
	return (255 << 24 | color.r << 16 | color.g << 8 | color.b);
}

void renderPixel(int x, int y, t_rgb color, t_data *data)
{
	mlx_pixel_put(data->mlx_data.mlx, data->mlx_data.win, x, y, colorToInt(color));
}

void renderImage(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->mlx_data.height)
	{
		x = 0;
		while (x < data->mlx_data.width)
		{
			t_rgb pixelColor = (t_rgb){(int)(((float)x / (float)data->mlx_data.width) * 255), (int)(((float)y / (float)data->mlx_data.height) * 255), 255};
			renderPixel(x, y, pixelColor, data);
			x++;
		}
		y++;
	}
	
	mlx_loop(data->mlx_data.mlx);
}