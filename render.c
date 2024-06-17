/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:07:44 by ctremino          #+#    #+#             */
/*   Updated: 2024/06/17 20:00:38 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

//put a pixel in my image buffer

static  void my_pixel_put(int x, int y, t_img * img, int color)
{
    int pixel_movement;


    // Calcular la posición del píxel en el buffer
    pixel_movement = (y * img->line_len) + (x * (img->bpp / 8));

    // Colocar el color en la posición calculada del buffer
    *(unsigned int *)(img->pixels_ptr + pixel_movement) = color;
}

	
//prueba1
static void manage_pixel(int x, int y, t_fractal *fractal)
{
    t_complex z;
    t_complex c;
    int i;
    int color;

    // Inicialización
    z.real = 0.0;
    z.imaginary = 0.0;

    // Escalar las coordenadas del pixel para el conjunto de Mandelbrot
    c.real = (map(x, 0, fractal->WIDTH, -2, 2)*(1 /fractal->zoom)) + fractal->shift_x;
    c.imaginary = (map(y, 0, fractal->HEIGHT, -2, 2)*(1/fractal->zoom)) + fractal->shift_y;

    // Iterar para ver si el punto escapa
    i = 0;
    while (i < fractal->image_quality_iteration)
    {
        z = sum_complex(square_complex(z), c);
        if ((z.real * z.real) + (z.imaginary * z.imaginary) > 4)
        {
            // Valor escapado
            color = map(i, 0, fractal->image_quality_iteration, WHITE, BLACK); 
            my_pixel_put(x, y, &fractal->img, color);
            return;
        }
        ++i;
    }

    // Si no escapa, es parte del conjunto de Mandelbrot
    my_pixel_put(x, y, &fractal->img, GREEN_FLUORESCENT);
}





void    fractal_render(t_fractal *fractal)
{
	int x;
	int y;
	
y = -1;
	while (++y < fractal->HEIGHT)
	{
		x = -1;
		while (++x < fractal->WIDTH)
		{
			manage_pixel(x, y, fractal);
		}
	}

	mlx_put_image_to_window(fractal->mlx_connection,
												fractal->mlx_window,
												fractal->img.img_ptr,
												0, 0);	

}