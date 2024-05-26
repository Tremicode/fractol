/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:07:44 by ctremino          #+#    #+#             */
/*   Updated: 2024/05/26 16:05:23 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//put a pixel in my image buffer

static  void my_pixel_put(int x, int y, t_img * img, int color)
{
	int pixel_movement;
	pixel_movement = ( y * img->line_len) + (x * (img->bpp / 8));
	/**(img->pixels_ptr + pixel_movement) = color;*/
	*(unsigned int *)(img ->pixels_ptr + pixel_movement) = color;
}

//check if the point is mandelbrot or not (imprtant)

static void    manage_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;
	
	i = 0;
	// 1 iteration
	z.real = 0.0;
	z.imaginary = 0.0;
	// pixel coordinate scaled to fint mandelbrot needs
	c.real = map(x, -2, +2, 0, WIDTH) + fractal->shift_x;
	c.imaginary = map(y, +2, -2, 0, HEIGHT) + fractal->shift_y;
	//printf("%d \n",fractal->image_quality_iteration);
	//exit(1);
	//how many times to iterate z 2 +c to check if the point scape
	while  (i < 200)
	{
		z = sum_complex(square_complex(z), c);
		if((z.real * z.real) + (z.imaginary * z.imaginary) > 4) //value escaped, hypotenuse >2 i asunnw the point escaped
		{
			color = map(i, BLACK, WHITE, 0, 400); 
			my_pixel_put(x, y,&fractal->img, color); 
			return ;
		}
		++i;
		//printf("%f %f %d \n",z.real,z.imaginary, i);
		
	}
	
	// if we are insade we are in mandelbrot
	my_pixel_put(x, y, &fractal->img, GREEN_FLUORESCENT); 
}




void    fractal_render(t_fractal *fractal)
{
	int x;
	int y;
	
y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			manage_pixel(x, y, fractal);
		}
	}

	mlx_put_image_to_window(fractal->mlx_connection,
							fractal->mlx_window,
							fractal->img.img_ptr,
							0, 0);	

}