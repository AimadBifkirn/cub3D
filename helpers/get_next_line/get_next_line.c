/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 20:18:30 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/17 11:25:24 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube.h"

char	*reset_res(char *reserve)
{
	char	*newres;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (reserve[i] && reserve[i] != '\n')
		i++;
	if (reserve[i] == '\n')
		i++;
	newres = ft_malloc((ft_strlen(reserve) - i) + 1);
	if (!newres)
		return (NULL);
	while (reserve[i])
	{
		newres[j] = reserve[i];
		j++;
		i++;
	}
	newres[j] = '\0';
	ft_free (reserve);
	reserve = NULL;
	return (newres);
}

char	*read_mine(int fd)
{
	char	*r;
	ssize_t	i;

	i = 0;
	r = ft_malloc((size_t)(BUFFER_SIZE + 1));
	if (!r)
		return (NULL);
	i = read(fd, r, BUFFER_SIZE);
	if (i <= 0)
	{
		ft_free (r);
		r = NULL;
		return (NULL);
	}
	r[i] = '\0';
	return (r);
}

char	*get_line(char *reserve)
{
	size_t	i;
	char	*line;

	i = 0;
	while (reserve[i] && reserve[i] != '\n')
		i++;
	line = ft_malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (reserve[i] && reserve[i] != '\n')
	{
		line[i] = reserve[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*readed;
	static char	*reserve;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (!ft_strchr(reserve, '\n'))
	{
		readed = read_mine(fd);
		if (!readed)
			break ;
		reserve = ft_strjoin(reserve, readed);
	}
	if (!reserve)
		return (NULL);
	line = get_line (reserve);
	reserve = reset_res(reserve);
	if (!*reserve)
	{
		ft_free (reserve);
		reserve = NULL;
	}
	return (line);
}
