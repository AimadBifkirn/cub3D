/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:43:48 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/20 21:13:47 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	start_map(char *line, int fd)
{
	int	i;
	int	ismap;

	ismap = 0;
	while (line)
	{
		i = 0;
		while (line[i])
		{
			if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			{
				ismap = 1;
				break ;
			}
			i++;
		}
		if (ismap == 1)
			return (extruct_map(line, fd));
		ft_free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	return (1);
}

int	ft_vid(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	valid_char(char *line, int *val1, int *val2)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0'
			&& line[i] != '\0' && line[i] != 'W' && line[i] != 'N'
			&& line[i] != 'E' && line[i] != 'O' && line[i] != 'S')
		{
			ft_error_el("invalid character \n");
		}
		i++;
		if (*val1 && *val2)
			ft_error("map must not separated\n");
		*val1 = 1;
	}
	if (ft_vid(line))
		*val2 = 1;
}

void	limiters_valmap(char *line, int fd, t_elements *element)
{
	int	col;
	int	val1;
	int	val2;

	val1 = 0;
	val2 = 0;
	while (line)
	{
		valid_char(line, &val1, &val2);
		element->map->rows++;
		col = ft_strlen(line);
		if (element->map->colomns < col)
			element->map->colomns = col;
		ft_free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
}

int	extruct_map(char *line, int fd)
{
	int			val1;
	int			val2;
	int			i;
	t_elements	*element;

	element = getter();
	element->map->rows = 0;
	val1 = 0;
	val2 = 0;
	limiters_valmap(line, fd, element);
	element->map->map = ft_malloc(sizeof(char *) * (element->map->rows + 1));
	if (!element)
		ft_error_el("ellocation failed \n");
	i = 0;
	while (i < element->map->rows)
	{
		element->map->map[i] = ft_malloc(sizeof(char) * (element->map->colomns
					+ 1));
		if (!element->map->map[i])
			ft_error_el("allocation failed \n");
		element->map->map[i][element->map->colomns] = '\0';
		i++;
	}
	element->map->map[i] = NULL;
	return (1);
}
