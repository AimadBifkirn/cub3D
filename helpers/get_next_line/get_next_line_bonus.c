/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 06:44:09 by zmounji           #+#    #+#             */
/*   Updated: 2025/06/30 14:54:01 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	newres = malloc((ft_strlen(reserve) - i) + 1);
	if (!newres)
		return (NULL);
	while (reserve[i])
	{
		newres[j] = reserve[i];
		j++;
		i++;
	}
	newres[j] = '\0';
	free (reserve);
	return (newres);
}

char	*read_mine(int fd)
{
	char	*r;
	ssize_t	i;

	i = 0;
	r = malloc((size_t)(BUFFER_SIZE + 1));
	if (!r)
		return (NULL);
	i = read(fd, r, BUFFER_SIZE);
	if (i <= 0)
	{
		free (r);
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
	if (reserve[i] == '\n')
		line = malloc(i + 2);
	else
		line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (reserve[i] && reserve[i] != '\n')
	{
		line[i] = reserve[i];
		i++;
	}
	if (reserve[i] == '\n')
	{
		line[i] = reserve[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*stash[1048576];
	char		*readed;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1048576)
		return (NULL);
	while (!ft_strchr(stash[fd], '\n'))
	{
		readed = read_mine(fd);
		if (!readed)
			break ;
		stash[fd] = ft_strjoin(stash[fd], readed);
	}
	if (!stash[fd])
		return (NULL);
	line = get_line (stash[fd]);
	stash[fd] = reset_res(stash[fd]);
	if (!*stash[fd])
	{
		free (stash[fd]);
		stash[fd] = NULL;
	}
	return (line);
}
