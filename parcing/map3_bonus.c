/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:13:34 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/21 10:56:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

char	*get_we(t_elements *element, char *line, char *str)
{
	if (!str)
	{
		str = ft_strnext(line, "WE");
		if (str && element->we)
			ft_error_el("elements was duplicated");
		if (str)
			element->we = extruct_link(str);
	}
	return (str);
}

char	*get_ea(t_elements *element, char *line, char *str)
{
	if (!str)
	{
		str = ft_strnext(line, "EA");
		if (str && element->ea)
			ft_error_el("elements was duplicated");
		if (str)
			element->ea = extruct_link(str);
	}
	return (str);
}

int	extruct_elements(char *line)
{
	int			i;
	char		*str;
	t_elements	*element;

	i = 0;
	str = NULL;
	element = getter();
	str = get_no(element, line, str);
	str = get_so(element, line, str);
	str = get_we(element, line, str);
	str = get_ea(element, line, str);
	if (!str)
		str = get_f(element, line, str);
	if (!str)
		str = get_c(element, line, str);
	while (!str && line && line[i])
	{
		if (line[i] != ' ')
			ft_error_el("invalide character\n");
		i++;
	}
	return (str != NULL);
}

char	*extruct_link(char *str)
{
	int		i;
	int		l;
	int		j;
	char	*link;

	i = 0;
	l = 0;
	if (!str || !*str)
		return (NULL);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	j = i;
	while (str[i] && str[i] != ' ' && str[i] != '\t')
		i++;
	link = ft_malloc(i - j + 1);
	if (!link)
		return (NULL);
	link[i - j] = '\0';
	while ((l + j) < i)
	{
		link[l] = str[l + j];
		l++;
	}
	return (link);
}
