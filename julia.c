/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:49:16 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/14 13:21:25 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h> // Para la función exit

static long	convert_int_part(char **s)
{
	long	int_part;

	int_part = 0;
	while (**s >= '0' && **s <= '9')
	{
		int_part = int_part * 10 + (**s - '0');
		++(*s);
	}
	return (int_part);
}

static double	convert_fraction_part(char **s, double *divisor)
{
	double	fraction_part;

	fraction_part = 0;
	if (**s == '.')
	{
		++(*s);
		while (**s >= '0' && **s <= '9')
		{
			*divisor *= 10;
			fraction_part += ((**s - '0') / (*divisor));
			++(*s);
		}
	}
	return (fraction_part);
}

double	atofdouble(char *s)
{
	long	int_part;
	double	fraction_part;
	double	divisor;
	int		sign;

	int_part = 0;
	fraction_part = 0;
	divisor = 1;
	sign = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		++s;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -sign;
		++s;
	}
	int_part = convert_int_part(&s);
	fraction_part = convert_fraction_part(&s, &divisor);
	if (*s != '\0')
		exit(1);
	return ((int_part + fraction_part) * sign);
}
