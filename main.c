/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 00:21:04 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/21 23:37:16 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

int	main(int ac, char**av)
{
	t_data	data;

	if (ac == 1)
	{
		write(1, "Fractales:\n-> mandelbrot\n-> julia\n-> burning_ship\n", 50);
		exit(0);
	}
	else
	{
		data.av1 = &av[1];
		data.z_julia = 1;
		data.fra = (t_fra){0, 0, 0, 0, 0, 0, 0, 0xffffff, 1, 1, 1, 0, -2, 0};
		init_mlx(&data);
		mlx_mouse_hook(data.mlx_win, &mouse_controls, &data);
		mlx_hook(data.mlx_win, 17, 0, &close_window, &data);
		mlx_hook(data.mlx_win, 2, 1L<<0, &keyboard_input, &data);
		fprintf(stderr, "%f/n", data.fra.z);
		mlx_key_hook(data.mlx_win, &keyboard_input, &data);
		mlx_loop_hook(data.mlx, &render, &data);
		mlx_loop(data.mlx);
	}
	return (0);
}
