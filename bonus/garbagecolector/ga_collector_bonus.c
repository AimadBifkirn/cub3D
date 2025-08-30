/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ga_collector_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abifkirn <abifkirn@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:38:30 by zmounji           #+#    #+#             */
/*   Updated: 2025/08/21 15:36:55 by abifkirn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube_bonus.h"

void	add_back(t_collecter *new_node)
{
	t_collecter	*tmp;
	t_collecter	**alloc_head;

	alloc_head = getter_garbage();
	if (!alloc_head || !*alloc_head)
	{
		*alloc_head = new_node;
		return ;
	}
	tmp = *alloc_head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

void	*ft_malloc(size_t size)
{
	void		*mem;
	t_collecter	*new_node;

	mem = malloc(size);
	if (!mem)
	{
		perror("minishell: malloc");
		ft_free_all();
		exit(1);
	}
	new_node = malloc(sizeof(t_collecter));
	if (!new_node)
	{
		free(mem);
		perror("minishell: malloc");
		ft_free_all();
		exit(1);
	}
	new_node->single1 = mem;
	new_node->next = NULL;
	add_back(new_node);
	return (mem);
}

void	free_images(void)
{
	t_elements	*element;
	int			i;

	element = getter();
	i = -1;
	while (++i < 6)
	{
		if (element->textures[i].img_ptr)
			mlx_destroy_image(element->mlx, element->textures[i].img_ptr);
		element->textures[i].img_ptr = NULL;
	}
	if (element->img)
		mlx_destroy_image(element->mlx, element->img);
	i = -1;
	while (++i < 10)
	{
		if (element->enemy && element->enemy->textures[i].img_ptr)
			mlx_destroy_image(element->mlx, \
			element->enemy->textures[i].img_ptr);
		element->textures[i].img_ptr = NULL;
	}
	destroy_win_des(element);
}

void	ft_free_all(void)
{
	t_collecter	*tmp;
	t_collecter	**alloc_head;

	alloc_head = getter_garbage();
	free_images();
	while (alloc_head && *alloc_head)
	{
		tmp = *alloc_head;
		*alloc_head = (*alloc_head)->next;
		free(tmp->single1);
		free(tmp);
	}
}

void	ft_free(void *pointer)
{
	t_collecter	*current;
	t_collecter	*prev;
	t_collecter	**alloc_head;

	alloc_head = getter_garbage();
	prev = NULL;
	current = *alloc_head;
	while (current)
	{
		if (current->single1 == pointer)
		{
			if (prev)
				prev->next = current->next;
			else
				*alloc_head = current->next;
			free(current->single1);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}
