/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:49:16 by ctremino          #+#    #+#             */
/*   Updated: 2024/12/12 19:32:33 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	atofdouble(char *s)
{
	long	int_part;
	double	fraction_part;
	double	divisor;
	int	sign;

	int_part = 0;
	fraction_part = 0;
	divisor = 1;
	sign = +1;

	while ((*s >= 9 && *s <= 13) || 32 == *s)
		++s;
	while ('-' == *s || '+' == *s)
		if ('-' == *s++)
			sign = -sign;
	while (*s != '.' && *s)
		int_part = (int_part * 10) + (*s++ - 48);
	if ('.' == *s)
		++s;
	while (*s)
	{
		divisor /= 10;
		fraction_part = fraction_part + (*s++ - 48) * divisor;
	}
	return ((int_part + fraction_part) * sign);
}