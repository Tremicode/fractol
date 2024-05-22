/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctremino <ctremino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:07:42 by ctremino          #+#    #+#             */
/*   Updated: 2024/05/12 12:08:46 by ctremino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int ft_strncmp(char *s1, char *s2, int n)
{
    if (NULL == s1 || NULL == s2 || n <= 0)
        return(0);
    while (*s1 == *s2 && n > 0 && *s1 != '\0') //1 or 0
    {
        ++s1;
        ++s2;
        --n;
    }
    return(*s1 -*s2);

}
void    putstr_fd(char *s, int fd)
{
    if (NULL == s || fd < 0)
        return;
    if (*s != '\0')
    {
        write(fd, s, 1); //buf: n:
        putstr_fd( s + 1, fd); // s:
    }
}