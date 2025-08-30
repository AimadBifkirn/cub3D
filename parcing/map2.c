/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 20:34:52 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/20 20:55:48 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	ft_error_el(const char *str)
{
	write(2, "Error\n", 7);
	write(2, str, ff_strlen(str));
	ft_free_all();
	exit(1);
}

void	ft_esc(const char *str)
{
	write(2, str, ff_strlen(str));
	ft_free_all();
	exit(42);
}

char	*ft_strnext(char *haystack, const char *needle)
{
	int	i;
	int	j;

	i = 0;
	while (haystack && haystack[i])
	{
		j = 0;
		while (needle && needle[j] && (haystack[i + j] == needle[j]))
			j++;
		if (needle[j] == '\0')
		{
			while (haystack && (haystack[i + j] == '\t' || haystack[i \
				+ j] == ' '))
				j++;
			return (haystack + i + j);
		}
		i++;
	}
	return (NULL);
}

char	*get_c(t_elements *element, char *line, char *str)
{
	char	**s_ar;
	int		col;

	str = ft_strnext(line, "C");
	if (str && element->c)
		ft_error_el("elements was duplicated  -------\n");
	if (str)
	{
		element->c = ft_malloc(sizeof(t_color));
		if (!element->c)
			ft_error_el("can not allocat");
		ft_bzero(element->c, sizeof(t_color));
		s_ar = ft_split(str, ',');
		col = 0;
		while (s_ar[col])
			col++;
		if (col != 3)
			ft_error_el("argument of coloro argb not correct\n");
		element->c->a = ft_atoi(s_ar[0]);
		element->c->b = ft_atoi(s_ar[1]);
		element->c->c = ft_atoi(s_ar[2]);
	}
	return (str);
}

char	*get_f(t_elements *element, char *line, char *str)
{
	char	**s_ar;
	int		col;

	str = ft_strnext(line, "F");
	if (str && element->f)
	{
		ft_error_el("elements was duplicated ************\n");
	}
	if (str)
	{
		element->f = ft_malloc(sizeof(t_color));
		if (!element->f)
			ft_error_el("can not allocat");
		ft_bzero(element->f, sizeof(t_color));
		s_ar = ft_split(str, ',');
		col = 0;
		while (s_ar[col])
			col++;
		if (col != 3)
			ft_error_el("argument of coloro argb not correct\n");
		element->f->a = ft_atoi(s_ar[0]);
		element->f->b = ft_atoi(s_ar[1]);
		element->f->c = ft_atoi(s_ar[2]);
	}
	return (str);
}
