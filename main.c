/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 15:49:01 by ctremino          #+#    #+#             */
/*   Updated: 2024/05/25 19:07:37 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#include <stdlib.h>


int main(int ac, char **av) 
{   
    t_fractal   fractal;
    if ((2 == ac && !ft_strncmp(av[1], "mandelbrot", 10)) //s1: s2: n:
    || (4 == ac && !ft_strncmp(av[1], "julia", 5))) //s1: s2: n:
    {
        
        fractal.name = av[1];
        fractal_init(&fractal);
        
        fractal_render(&fractal);
        mlx_loop(fractal.mlx_connection);
        // Código para manejar mandelbrot o julia set
    } else {
        putstr_fd(ERROR_MESSAGE, STDERR_FILENO);// s: fd:
        exit(EXIT_FAILURE); //status:
    }

    return 0;
}




