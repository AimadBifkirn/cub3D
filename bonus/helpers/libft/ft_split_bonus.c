/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:23:31 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/21 15:33:16 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cube_bonus.h"

static char	**free_array(char **ptr, int i)
{
	while (i > 0)
	{
		i--;
		ft_free(ptr[i]);
		ptr[i] = NULL;
	}
	ft_free(ptr);
	ptr = NULL;
	return (NULL);
}

static int	ft_count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
		else
		{
			i++;
		}
	}
	return (count);
}

static char	*ft_putword(char const *s, int start, int word_len)
{
	char	*word;
	int		j;

	j = 0;
	word = (char *)ft_malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (NULL);
	while (j < word_len)
	{
		word[j] = s[start];
		j++;
		start++;
	}
	word[j] = '\0';
	return (word);
}

static char	**ft_split_words(char const *s, char c, char **s2, int num_words)
{
	int	i;
	int	word;
	int	word_len;
	int	start;

	i = 0;
	word = 0;
	while (word < num_words)
	{
		word_len = 0;
		while (s[i] && s[i] == c)
			i++;
		start = i;
		while (s[i] && s[i] != c)
		{
			word_len++;
			i++;
		}
		s2[word] = ft_putword(s, start, word_len);
		if (!s2[word])
			return (free_array(s2, word));
		word++;
	}
	s2[word] = NULL;
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	num_words;

	if (!s)
		return (NULL);
	num_words = ft_count_words(s, c);
	s2 = (char **)ft_malloc(sizeof(char *) * (num_words + 1));
	if (!s2)
		return (NULL);
	s2 = ft_split_words(s, c, s2, num_words);
	return (s2);
}
