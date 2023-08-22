/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:22:00 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/28 22:57:12 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx/mlx.h"

void	info_display(t_data *data);

int	render(t_data *data)
{
	data->len = fra_strlen(*data->av1);
	data->check = fra_strncmp(*data->av1, "julia", 5);
	if (data->check == 0 && data->len == 5)
		julia (&data->img, data->fra, data);
	else if (data->len == 10)
	{
		data->check = fra_strncmp(*data->av1, "mandelbrot", 10);
		if (data->check == 0)
			mandelbrot (&data->img, data->fra, data);
		else
			reject();
	}
	else if (data->len == 12)
	{
		data->check = fra_strncmp(*data->av1, "burning_ship", 12);
		if (data->check == 0)
			burning_ship (&data->img, data->fra);
		else
			reject();
	}
	else
		reject();
	pixel_put(&data->img, 350, 350, 0xFF0000);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img_ptr, 0, 0);
	info_display(data);
	return (0);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	if (x < WID && x > 0 && y < HEI && y > 0)
	{
		pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(int *)pixel = color;
	}
}

int	set_color(t_fra *fra, t_img *img)
{


	if (fra->i == -2)
		pixel_put(img, fra->col, fra->row, 0x000000);
	if (fra->i >= 1 && fra->i < 10)
		pixel_put(img, fra->col, fra->row, fra->c + (fra->i * 1000));
	if (fra->i >= 2 && fra->i < 6)
		pixel_put(img, fra->col, fra->row, fra->c + (fra->i * 2000));
	if (fra->i >= 6 && fra->i < 10)
		pixel_put(img, fra->col, fra->row, fra->c + (fra->i * 3000));
	if (fra->i >= 10 && fra->i < 20)
		pixel_put(img, fra->col, fra->row, fra->c + (fra->i * 4000));
	if (fra->i >= 20 && fra->i < 30)
		pixel_put(img, fra->col, fra->row, fra->c + (fra->i * 5000));
	if (fra->i >= 30 && fra->i < 100)
		pixel_put(img, fra->col, fra->row, fra->c + (fra->i * 5000));
	if (fra->i >= 100 && fra->i < 400)
		pixel_put(img, fra->col, fra->row, fra->c + (fra->i * 5000));
	if (fra->i == 400)
		pixel_put(img, fra->col, fra->row, 0x000000);
	else
		pixel_put(img, fra->col, fra->row, fra->c + (fra->i * 1000));


	return (0);
}
