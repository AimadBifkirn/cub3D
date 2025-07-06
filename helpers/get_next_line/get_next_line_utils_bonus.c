/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 06:44:27 by zmounji           #+#    #+#             */
/*   Updated: 2025/06/29 12:04:29 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_str;

	if (!s1)
		return (s2);
	new_str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s1, ft_strlen(s1));
	ft_memcpy(new_str + ft_strlen(s1), s2, ft_strlen(s2));
	new_str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free (s1);
	s1 = NULL;
	free (s2);
	s2 = NULL;
	return (new_str);
}

void	ft_memcpy(char *s1, char *s2, size_t i)
{
	size_t	j;

	j = 0;
	while (j < i)
	{
		s1[j] = s2[j];
		j++;
	}
}
