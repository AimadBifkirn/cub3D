/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:28:16 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/21 10:56:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

int	help_copy(t_elements *element, char *line, int *j)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line && line[i] && line[i] != ' ' && line[i] != '1' \
		&& line[i] != '0' && line[i] != '\0' && line[i] != 'W' \
		&& line[i] != 'N' && line[i] != 'E' && line[i] != 'O' && line[i] != 'S')
		{
			ft_error_el("invalid character NOO \n");
		}
		element->map->map[*j][i] = line[i];
		i++;
	}
	return (i);
}

int	copy_map(char *line, int fd)
{
	int			i;
	int			j;
	t_elements	*element;

	element = getter();
	j = 0;
	while (line)
	{
		i = help_copy(element, line, &j);
		while (i < element->map->colomns)
		{
			element->map->map[j][i] = ' ';
			i++;
		}
		element->map->map[j][i] = '\0';
		j++;
		ft_free (line);
		line = NULL;
		line = get_next_line(fd);
	}
	close (fd);
	return (1);
}

char	*extruct_tex_col(char *line, int fd)
{
	int	number;

	number = 0;
	while (line && (number < 6))
	{
		if (ft_strnext(line, "NO") || ft_strnext(line, "SO") \
		|| ft_strnext(line, "WE") || ft_strnext(line, "EA") \
		|| ft_strnext(line, "F") || ft_strnext(line, "C"))
		{
			number += extruct_them(line);
		}
		if (line)
		{
			ft_free (line);
			line = NULL;
		}
		line = get_next_line(fd);
	}
	if (number < 6)
		ft_error_el("element or more are absents");
	return (line);
}

int	extruct_mmp(char *line, int fd, int i, int ismap)
{
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
		{
			return (copy_map(line, fd));
		}
		if (line)
		{
			ft_free (line);
			line = NULL;
		}
		line = get_next_line(fd);
	}
	return (1);
}

int	upload_map(char **argv)
{
	int		fd;
	char	*line;
	int		i;
	int		ismap;

	ismap = 0;
	i = 0;
	fd = open (argv[1], O_RDONLY, 0644);
	if (fd < 0)
		ft_error_el("failed fd\n");
	line = NULL;
	line = get_next_line(fd);
	line = extruct_tex_col(line, fd);
	return (extruct_mmp(line, fd, i, ismap));
}
