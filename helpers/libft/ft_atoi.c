/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:35:12 by zmounji           #+#    #+#             */
/*   Updated: 2025/06/23 15:54:45 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

int	ft_atoi(const char *str)
{
	long	result;

	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
	{
		str++;
	}
	if (*str < '0' || *str > '9')
	{
        ft_error_el(" invalid character \n");
	}
	while (*str >= '0' && *str <= '9')
	{
        if (result >= ((2147483647 / 10) + (*str - '0')))
            ft_error_el("Avoid over floing\n");
		result = result * 10 + (*str - '0');
		str++;
	}
    while (*str)
    {
        if (*str != ' ')
            ft_error_el("color number not good\n");
        str++;
    }
    
    if (result > 255)
        ft_error_el("Avoid over floing\n");
    
    return (result );
}