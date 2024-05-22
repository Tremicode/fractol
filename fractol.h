/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:18:49 by ctremino          #+#    #+#             */
/*   Updated: 2024/05/21 22:30:22 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <math.h>
# include <stdio.h>  // debugging
# include <stdlib.h> //malloc
# include <unistd.h>

# define HEIGHT 800
# define WIDTH 800

// (formato RGB hexadecimal)
# define BLACK         0x000000 // Negro
# define WHITE         0xFFFFFF // Blanco
# define RED           0xFF0000 // Rojo
# define GREEN         0x00FF00 // Verde
# define BLUE          0x0000FF // Azul
# define YELLOW        0xFFFF00 // Amarillo
# define CYAN          0x00FFFF // Cian
# define MAGENTA       0xFF00FF // Magenta
# define HOT_PINK      0xFF69B4 // Rosa fosforescente
# define LIME_GREEN    0x32CD32 // Verde lima
# define ELECTRIC_PURPLE 0xBF00FF // Púrpura eléctrico
# define NEON_GREEN           0x39FF14 // Verde neón
# define SHOCKING_PINK        0xFC0FC0 // Rosa impactante
# define VIVID_ORANGE         0xFFA500 // Naranja vivo
# define FLAMINGO_PINK        0xFC8EAC // Rosa flamenco
# define LASER_LEMON          0xFFFF66 // Limón láser
# define ULTRAMARINE_BLUE     0x3F00FF // Azul ultramarino
# define RAZZMATAZZ           0xE3256B // Rojo frambuesa
# define SPRING_GREEN         0x00FF7F // Verde primavera
# define ELECTRIC_LIME        0xCCFF00 // Lima eléctrica
# define OUTRAGEOUS_ORANGE    0xFF6E4A // Naranja escandaloso



# define ERROR_MESSAGE "please enter \n\t\"./fractol mandelbrot\" or \n\t\"./fractol julia <value_1> <value_2>\"\n"

typedef struct  s_img
{
	void    *img_ptr; // map to find imagen
	char    *pixels_ptr; // list pixeles de la imagen
	int     bpp;//label bits en cada pixel
	int     endian;
	int     line_len; // how many pixeles per line
}               t_img; // nickname 

//fractal id, mlx.image, hooks value
typedef struct  s_fractal
{
	char	*name;
	void	*mlx_connection; // mlx_init
	void	*mlx_window; 
	t_img	img;// white canvas
	double escape_value; // hypotenuse
	int     image_quality_iteration; // quality interations speed
}       t_fractal;

typedef struct s_complex // estructura creada porque no compila.
{
	double  real;
	double  imaginary;
}       t_complex;



/*fractal_render(&fractal); //render*/
void    fractal_render(t_fractal *fractal);

int		ft_strncmp(char *s1, char *s2, int n);
void	putstr_fd(char *s, int fd);
void    fractal_init(t_fractal *fractal);

//math
double      map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex   sum_complex(t_complex z1, t_complex z2);
t_complex   square_complex(t_complex z);


#endif
