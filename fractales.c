/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:22:14 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/28 23:12:57 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

int	mandelbrot(t_img *img, t_fra fra, t_data *data)
{
	(void)data;
	int p;

	while (fra.row++ < HEI)
	{
		fra.col = 0;
		while (fra.col++ < WID)
		{
			fra.c_r = (((fra.col + fra.l_r - (WID / 2.0)) * 4.0) / WID / fra.z);
			fra.c_i = (((fra.row + fra.u_d - (HEI / 2.0)) * 4.0) / HEI / fra.z);
			fra.x = 0;
			fra.y = 0;
			fra.i = 0;
			p = sqrt((fra.c_r - 0.25) * (fra.c_r - 0.25) + (fra.c_i * 2.5) * (fra.c_i));
			if (((fra.c_r + 1) * (fra.c_r + 1) + fra.c_i * fra.c_i) < 0.0625)
			{
			 	pixel_put(img, fra.col, fra.row, 0x000000);
			}
			else if (fra.c_r < (p - 4.0 * p -1 * p / 0.25))
			{
				pixel_put(img, fra.col, fra.row, 0x000000);
			}
			else
			{
				while ((fra.x * fra.x) + (fra.y * fra.y) <= 4 && fra.i < 400)
				{
					fra.new = (fra.x * fra.x) - (fra.y * fra.y) + fra.c_r;
					fra.y = 2 * fra.x * fra.y + fra.c_i;
					fra.x = fra.new;
					fra.i++;
				}
				set_color (&fra, img);
			}
		}
	}
	return (0);
}

int	julia(t_img *img, t_fra fra, t_data *data)
{
	while (fra.row++ < WID)
	{
		fra.col = 0;
		while (fra.col++ < HEI)
		{
			fra.c_r = (((fra.col + fra.l_r - (WID / 2.0)) * 4.0) / WID	/ data->fra.z);
			fra.c_i = (((fra.row + fra.u_d - (HEI / 2.0)) * 4.0) / HEI / data->fra.z);
			fra.i = 0;
			while ((fra.c_r * fra.c_r) + (fra.c_i * fra.c_i)
				<= 4 && fra.i < 400)
			{
				fra.new = (fra.c_r * fra.c_r) - (fra.c_i * fra.c_i) + fra.multi;
				fra.c_i = 2 * fra.c_r * fra.c_i + fra.multi;
				fra.c_r = fra.new;
				fra.i++;
			}
			set_color(&fra, img);
		}
	}
	return (0);
}

int	burning_ship(t_img *img, t_fra fra)
{
	while (fra.row++ < HEI)
	{
		fra.col = 0;
		while (fra.col++ < WID)
		{
			fra.c_r = (((fra.col + fra.l_r - (WID / 2.0)) * 4.0) / WID / fra.z);
			fra.c_i = (((fra.row + fra.u_d - (HEI / 2.0)) * 4.0) / HEI / fra.z);
			fra.x = 0;
			fra.y = 0;
			fra.i = 0;
			while ((fra.x * fra.x) + (fra.y * fra.y) <= 4 && fra.i < 400)
			{
				fra.new = fabs((fra.x * fra.x)) - fabs((fra.y * fra.y))
					+ fra.c_r;
				fra.y = fabs(2 * fra.x * fra.y) + fra.c_i;
				fra.x = fra.new;
				fra.i++;
			}
			set_color (&fra, img);
		}
	}
	return (0);
}

int black_part(t_fra fra)
{
	int p;

	p = sqrt((fra.c_r - 0.25) * (fra.c_r - 0.25) + fra.c_i * fra.c_i);
	if (fra.c_r < (p - 2 * p * p + 0.25))
		return (-2);
	if (((fra.c_r + 1) * (fra.c_r + 1) + fra.c_i * fra.c_i) < 0.0625)
		return (-2);
	return (0);
}
