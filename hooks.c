/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:37:44 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/28 23:13:40 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

int	keyboard_input(int keycode, t_data *data)
{
	if (keycode == 65307)
		reject();
	if (keycode == 65363)
		data->fra.l_r += 25;
	// if (keycode == 124)
	// 	data->fra.l_r += 25;
	if (keycode == 65361)
		data->fra.l_r -= 25;
	// if (keycode == 123)
	// 	data->fra.l_r -= 25;
	if (keycode == 65364)
		data->fra.u_d += 25;
	// if (keycode == 125)
	// 	data->fra.u_d += 25;
	if (keycode == 65362)
		data->fra.u_d -= 25;
	// if (keycode == 126)
	// 	data->fra.u_d -= 25;
	if (keycode == 113)
		data->fra.multi += 0.012;
	if (keycode == 45)
		data->fra.multi -= 0.012;
	return (0);
}

int	mouse_controls(int mousecode, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (mousecode == 4)
	{
		data->fra.z *= 1.5;
		data->fra.l_r = 1.5 * data->fra.l_r;
		data->fra.u_d = 1.5 * data->fra.u_d;
	}
	if (mousecode == 5)
	{
		data->fra.z /= 1.5;
		data->fra.l_r = data->fra.l_r / 1.5;
		data->fra.u_d = data->fra.u_d / 1.5;
	}
	// if (mousecode == 4)
	// 	data->z_julia *= 1.2;
	// if (mousecode == 5)
	// 	data->z_julia *= 0.8;
	if (mousecode == 2)
	{
		data->fra.u_d = 1;
		data->fra.l_r = 1;
		data->fra.z = 1;
		data->z_julia = 1;
	}
	if (mousecode == 1)
		data->fra.c = data->fra.c + rand();
	return (0);
}
