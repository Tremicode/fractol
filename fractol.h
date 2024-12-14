/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 16:18:49 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/14 19:12:20 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <math.h>
# include <stdio.h>  // debugging
# include <stdlib.h> //malloc
# include <unistd.h>

// (formato RGB hexadecimal)
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define YELLOW 0xFFFF00
# define CYAN 0x00FFFF
# define MAGENTA 0xFF00FF
# define HOT_PINK 0xFF69B4
# define LIME_GREEN 0x32CD32
# define ELECTRIC_PURPLE 0xBF00FF
# define NEON_GREEN 0x39FF14
# define SHOCKING_PINK 0xFC0FC0
# define VIVID_ORANGE 0xFFA500
# define FLAMINGO_PINK 0xFC8EAC
# define LASER_LEMON 0xFFFF66
# define ULTRAMARINE_BLUE 0x3F00FF
# define RAZZMATAZZ 0xE3256B
# define SPRING_GREEN 0x00FF7F
# define ELECTRIC_LIME 0xCCFF00
# define OUTRAGEOUS_ORANGE 0xFF6E4A
# define NEON_PINK 0xFF6EC7
# define GREEN_FLUORESCENT 0x39FF14

# define ERROR_MESSAGE "enter\n\t\"./fractol mandelbrot\" or\n\t\"./fractol julia <value_1> <value_2>\"\n"

typedef struct s_img
{
	void	*img_ptr;
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}			t_img;

// fractal id, mlx.image, hooks value
typedef struct s_fractal
{
	char	*name;
	void	*mlx_connection;
	void	*mlx_window;
	t_img	img;
	double	escape_value;
	int		image_quality_iteration;
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
	int		height;
	int		width;

}			t_fractal;

int			process_close(t_fractal *fractal);

typedef struct s_complex
{
	double	real;
	double	imaginary;
}			t_complex;

void		fractal_init(t_fractal *fractal);

// fractal_render(&fractal); //render*/
void		fractal_render(t_fractal *fractal);
void		events(t_fractal *fractal);

// strings utils
int			ft_strncmp(char *s1, char *s2, int n);
void		putstr_fd(char *s, int fd);
double		atofdouble(char *s);

// fractal init
void		fractal_init(t_fractal *fractal);

// math
double		map(double *unum_omin_omax_nmin_nmax);
t_complex	sum_complex(t_complex z1, t_complex z2);
t_complex	square_complex(t_complex z);

// hooks events
int			process_key(int keysym, t_fractal *fractal);
int			process_mouse(int button, int x, int y, t_fractal *fractal);

#endif
