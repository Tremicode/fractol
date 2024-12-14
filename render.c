/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:07:44 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/14 13:07:41 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// Place a pixel in the image buffer, Calcul pixel position in the buffer,
// Place the color at the calculated position in the buffer
static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	pixel_movement;

	pixel_movement = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + pixel_movement) = color;
}

// Initialize complex number for Mandelbrot or Julia set
static void	mandelbrot_julia(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->real = fractal->julia_x;
		c->imaginary = fractal->julia_y;
	}
	else
	{
		c->real = z->real;
		c->imaginary = z->imaginary;
	}
}

static void	manage_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	z.real = (map(x, 0, fractal->WIDTH, -2, 2) * (1 / fractal->zoom))
		+ fractal->shift_x;
	z.imaginary = (map(y, 0, fractal->HEIGHT, -2, 2) * (1 / fractal->zoom))
		+ fractal->shift_y;
	mandelbrot_julia(&z, &c, fractal);
	while (i < fractal->image_quality_iteration)
	{
		z = sum_complex(square_complex(z), c);
		if ((z.real * z.real) + (z.imaginary * z.imaginary) > 4)
		{
			color = map(i, 0, fractal->image_quality_iteration, WHITE, BLACK);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		++i;
	}
	my_pixel_put(x, y, &fractal->img, GREEN_FLUORESCENT);
}
// Render the fractal image

void	fractal_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < fractal->HEIGHT)
	{
		x = -1;
		while (++x < fractal->WIDTH)
		{
			manage_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection, fractal->mlx_window,
		fractal->img.img_ptr, 0, 0);
}
