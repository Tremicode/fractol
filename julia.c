/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 17:49:16 by ctremino          #+#    #+#             */
/*   Updated: 2024/07/04 18:13:22 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double  atofdouble(char *s)
{
    long    int_part;
    double fraction_part;
    double  divisor;
    int sign;
    
    int_part = 0;
    fraction_part = 0;
    divisor = 1;
    sign = +1;
    while ((*s >= 9 && *s <= 13)|| 32 == *s)//verifica espacio blanco, tab..
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
        fraction_part = fraction_part + (*s++ -48) * divisor;
    }
    return ((int_part + fraction_part) * sign);
    


    
}
/*// simplificado 

double atofdouble(char *s) 
{
    double result = 0.0;
    int sign = 1;
    int has_decimal = 0;
    double decimal_divisor = 1.0;

    // Salta los espacios iniciales
    while (*s == ' ' || (*s >= 9 && *s <= 13))
        s++;

    // Manejo del signo
    if (*s == '-') {
        sign = -1;
        s++;
    } else if (*s == '+') {
        s++;
    }

    // Procesamiento de la parte entera
    while (*s >= '0' && *s <= '9') {
        result = result * 10.0 + (*s - '0');
        s++;
    }

    // Procesamiento de la parte decimal
    if (*s == '.') {
        has_decimal = 1;
        s++;
        while (*s >= '0' && *s <= '9') {
            result = result * 10.0 + (*s - '0');
            decimal_divisor *= 10.0;
            s++;
        }
    }

    result = sign * result; //Aplica el signo y la parte decimal si existe
    if (has_decimal)
        result /= decimal_divisor;

    return result;
}*/


