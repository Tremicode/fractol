/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:49:01 by ctremino          #+#    #+#             */
/*   Updated: 2024/11/18 18:47:38 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <stdlib.h>


int main(int argc, char **argv) 
{   
    t_fractal   fractal;
    if (argc == 4 && !ft_strncmp(argv[1], "julia", 5))
    {
        fractal.name = argv[1];
        fractal.julia_x = atofdouble(argv[2]);
        fractal.julia_y = atofdouble(argv[3]);
    }
    else if ((argc == 2 && !ft_strncmp(argv[1], "mandelbrot", 10))) 
    {
        fractal.name = argv[1];
        // Código para manejar mandelbrot o julia set
    } else {
        putstr_fd(ERROR_MESSAGE, STDERR_FILENO);// s: fd:
        exit(EXIT_FAILURE); //status:
    }
        fractal_init(&fractal);
        fractal_render(&fractal);
        mlx_loop(fractal.mlx_connection);

    return 0;
}






