/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:13:34 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/20 20:48:30 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char	*get_no(t_elements *element, char *line, char *str)
{
	str = ft_strnext(line, "NO");
	if (str && element->no)
		ft_error_el("elements was duplicated");
	if (str)
	{
		element->no = extruct_link(str);
	}
	return (str);
}

char	*get_so(t_elements *element, char *line, char *str)
{
	if (!str)
	{
		str = ft_strnext(line, "SO");
		if (str && element->so)
			ft_error_el("elements was duplicated");
		if (str)
			element->so = extruct_link(str);
	}
	return (str);
}
