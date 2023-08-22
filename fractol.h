/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdefayes <jdefayes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 13:41:09 by jdefayes          #+#    #+#             */
/*   Updated: 2023/02/28 23:30:19 by jdefayes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <complex.h>

# define WID 700
# define HEI 700

typedef struct s_fra
{
	double	x;
	double	y;

	double	row;
	double	col;

	double	c_r;
	double	c_i;

	double	new;

	int		c;
	double	z;

	double	l_r;
	double	u_d;

	int		i;

	double	multi;
	char	*zoom;
}	t_fra;

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
	t_fra	fra;
	int		x;
	int		y;
	char	**av1;
	int		len;
	int		check;
	double	z_julia;
}	t_data;

int		main(int ac, char**av);
int		init_mlx(t_data *data);
int		close_window(t_data *data);

int		mouse_controls(int mousecode, int x, int y, t_data *data);
int		keyboard_input(int keycode, t_data *data);

int		fra_strlen(const char *s);
int		fra_strncmp(const char *s1, const char *s2, size_t n);
int		render(t_data *data);
void	pixel_put(t_img *img, int x, int y, int color);
int		set_color(t_fra *fra, t_img *img);
char	*fra_itoa(int n);

int		mandelbrot(t_img *img, t_fra fra, t_data *data);
int		julia(t_img *img, t_fra fra, t_data *data);
int		burning_ship(t_img *img, t_fra fra);
int		black_part(t_fra fra);

void	reject(void);
#endif
