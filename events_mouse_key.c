/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_mouse_key.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:56:18 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/14 17:48:28 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdio.h>

// keypress protype from manual
int	process_key(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		process_close(fractal);
	if (keysym == XK_Right)
		fractal->shift_x += (0.03 * (1 / fractal->zoom));
	else if (keysym == XK_Left)
		fractal->shift_x -= (0.03 * (1 / fractal->zoom));
	else if (keysym == XK_Up)
		fractal->shift_y -= (0.03 * (1 / fractal->zoom));
	else if (keysym == XK_Down)
		fractal->shift_y += (0.03 * (1 / fractal->zoom));
	else if (keysym == XK_plus || keysym == XK_KP_Add)
		fractal->image_quality_iteration += 5;
	else if (keysym == XK_minus || keysym == XK_KP_Subtract)
		fractal->image_quality_iteration -= 5;
	fractal_render(fractal);
	return (0);
}
/*close window esc or x*/

int	process_close(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_connection, fractal->img.img_ptr);
	mlx_destroy_display(fractal->mlx_connection);
	mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
	free(fractal->mlx_connection);
	exit(EXIT_SUCCESS);
}
// mouse zoom in 0.98 1.7 / zoom out 1.02 0.3

int	process_mouse(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button4)
	{
		fractal->zoom *= 1.3;
	}
	else if (button == Button5)
	{
		fractal->zoom *= 0.2;
	}
	fractal->shift_y = (map((double [5]){y, 0, fractal->height, -2, 2}) * (1
				/ fractal->zoom)) + fractal->shift_y;
	fractal->shift_x = (map((double [5]){x, 0, fractal->width, -2, 2}) * (1
				/ fractal->zoom)) + fractal->shift_x;
	fractal_render(fractal);
	return (0);
}

void	events(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window, KeyPress, KeyPressMask, process_key, fractal);
	mlx_hook(fractal->mlx_window, ButtonPress, ButtonPressMask, process_mouse,
		fractal);
	mlx_hook(fractal->mlx_window, DestroyNotify, StructureNotifyMask,
		process_close, fractal);
}
