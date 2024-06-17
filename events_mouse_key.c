/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:56:18 by ctremino          #+#    #+#             */
/*   Updated: 2024/06/17 20:02:11 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
#include <X11/keysym.h>
#include "minilibx-linux/mlx.h"




//keypress protype from manual
int process_Key(int Keysym, t_fractal *fractal)
{
   if (Keysym == XK_Escape)
       process_close(fractal);
     if (Keysym == XK_Right)
        fractal->shift_x -= (0.05 * (1/ fractal->zoom));
    else if (Keysym == XK_Left)
        fractal->shift_x += (0.05 * (1/fractal->zoom));
    else if (Keysym == XK_Up)
        fractal->shift_y += (0.05 * (1/fractal->zoom));
    else if (Keysym == XK_Down)
        fractal->shift_y -= (0.05 * (1/fractal->zoom));
    else if (Keysym == XK_plus || Keysym == XK_KP_Add)
            fractal->image_quality_iteration += 5;
    else if (Keysym == XK_minus || Keysym == XK_KP_Subtract)
            fractal->image_quality_iteration -= 5;
            
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
// mouse zoom 

int process_mouse(int button, int x, int y, t_fractal *fractal)
{
    if (button==Button4)// zoom in smooth = 0.98
    {
        fractal->zoom *=1.7;
    }
    else if (button==Button5)// zoom out smooth = 1.02
    {
        fractal->zoom *= 0.3;
    }
      fractal->shift_y = (map(y, 0, fractal->HEIGHT, -2, 2)*(1/fractal->zoom)) + fractal->shift_y;
     fractal->shift_x = (map(x, 0, fractal->WIDTH, -2, 2)*(1/fractal->zoom)) + fractal->shift_x;
    fractal_render(fractal);
    return(0);


}


void events(t_fractal *fractal) // events_init 
{
    mlx_hook(fractal->mlx_window, KeyPress, KeyPressMask, process_Key, fractal); // Teclado
    mlx_hook(fractal->mlx_window, ButtonPress, ButtonPressMask, process_mouse, fractal); // Mouse
    mlx_hook(fractal->mlx_window, DestroyNotify, StructureNotifyMask, process_close, fractal); // Cerrar ventana

}


