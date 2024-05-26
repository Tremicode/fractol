/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:56:18 by ctremino          #+#    #+#             */
/*   Updated: 2024/05/26 17:17:57 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
//#include "minilibx-linux/mlx.h"

//keypress protype from manual
int process_Key(int Keysym, t_fractal *fractal)
{
   if (Keysym == XK_Escape)
       process_close(fractal);
     if (Keysym == XK_Right)
        fractal->shift_x -= 0.5;
    else if (Keysym == XK_Left)
        fractal->shift_x += 0.5;
    else if (Keysym == XK_Up)
        fractal->shift_y -= 0.5;
    else if (Keysym == XK_Down)
        fractal->shift_y += 0.5;
    else if (Keysym == XK_plus)
            fractal-> image_quality_iteration += 5;
    else if (Keysym == XK_minus)
            fractal-> image_quality_iteration -= 5;
            
        fractal_render(fractal);// refresh the image
    /*printf("%d %f %f \n", Keysym, fractal->shift_x, fractal->shift_y);*/
    return 0;
}
/*close window esc or x*/
int    process_close(t_fractal *fractal)
{
    mlx_destroy_image(fractal->mlx_connection,fractal->img.img_ptr);
    mlx_destroy_display(fractal->mlx_connection);
    mlx_destroy_window(fractal->mlx_connection,fractal->mlx_window);
    free(fractal->mlx_connection);
    exit(EXIT_SUCCESS);
    
}



void events(t_fractal *fractal) // events_init 
{
    mlx_hook(fractal->mlx_window, KeyPress, KeyPressMask, process_Key, fractal); // Teclado
    //mlx_hook(fractal->mlx_window, ButtonPress, ButtonPressMask, process_mouse, fractal); // Mouse
    mlx_hook(fractal->mlx_window, DestroyNotify, StructureNotifyMask, process_close, fractal); // Cerrar ventana
}


