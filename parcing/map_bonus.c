/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:13:34 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/21 10:56:25 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

int	extruct_them(char *line)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	str = ft_strnext(line, "NO");
	if (!str)
		str = ft_strnext(line, "SO");
	if (!str)
		str = ft_strnext(line, "WE");
	if (!str)
		str = ft_strnext(line, "EA");
	if (!str)
		str = ft_strnext(line, "F");
	if (!str)
		str = ft_strnext(line, "C");
	while (!str && line && line[i])
	{
		if (line[i] != ' ')
			ft_error_el("invalide character\n");
		i++;
	}
	return (str != NULL);
}

void	map(char **argv)
{
	int		fd;
	int		number;
	char	*line;

	fd = open(argv[1], O_RDONLY, 0644);
	line = NULL;
	line = get_next_line(fd);
	number = 0;
	while (line && (number < 6))
	{
		number += extruct_elements(line);
		ft_free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	if (number < 6)
		ft_error_el("element or more are absents");
	start_map(line, fd);
	upload_map(argv);
	cheack_map();
}
