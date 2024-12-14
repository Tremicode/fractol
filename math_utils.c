/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 19:41:02 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/14 18:01:37 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

// from (0 to 799) (-2 to +2)

double	map(double *unum_omin_omax_nmin_nmax)
{
	double	unscaled_num;
	double	old_min;
	double	old_max;
	double	new_min;
	double	new_max;

	unscaled_num = unum_omin_omax_nmin_nmax[0];
	old_min = unum_omin_omax_nmin_nmax[1];
	old_max = unum_omin_omax_nmin_nmax[2];
	new_min = unum_omin_omax_nmin_nmax[3];
	new_max = unum_omin_omax_nmin_nmax[4];
	return (new_min + ((unscaled_num - old_min) * (new_max - new_min) / (old_max
				- old_min)));
}

// sum complex

t_complex	sum_complex(t_complex z1, t_complex z2)
{
	t_complex	result;

	result.real = z1.real + z2.real;
	result.imaginary = z1.imaginary + z2.imaginary;
	return (result);
}
// square is trickier

t_complex	square_complex(t_complex z)
{
	t_complex	result;

	result.real = (z.real * z.real) - (z.imaginary * z.imaginary);
	result.imaginary = 2 * z.real * z.imaginary;
	return (result);
}
