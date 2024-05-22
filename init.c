/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 18:35:55 by ctremino          #+#    #+#             */
/*   Updated: 2024/05/21 23:12:08 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>

// init
//mlx
// listening events
// hooks data
static void malloc_error(void)
{
	perror("Problems with malloc"); s:
	exit(EXIT_FAILURE);
}
void    data_init(t_fractal *fractal)
{
	fractal->escape_value = 4; // hypotenusa 2 al cuadrado 
	fractal->image_quality_iteration = 42;
}





void    fractal_init(t_fractal *fractal)
{
	fractal->mlx_connection = mlx_init();
	if (NULL == fractal->mlx_connection)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection,
										 800, 800,
										 fractal->name); 
	if (NULL ==fractal->mlx_window)
	{
		mlx_destroy_display(fractal->mlx_connection); 
		free(fractal->mlx_connection); 
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection,
										800, 800);
	if(NULL== fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_connection); //mlx_ptr:
		free(fractal->mlx_connection); 
		malloc_error();
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
												&fractal->img.bpp,
												&fractal->img.line_len,
												&fractal->img.endian);

		 //data_init(fractal);
}
//loop falta