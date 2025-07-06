/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:13:34 by zmounji           #+#    #+#             */
/*   Updated: 2025/06/30 14:44:02 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cube.h"

void	ft_error_el(const char *str)
{
	write(2, "Error\n", 7);
	write(2, str, ff_strlen(str));
    // leack truck
	exit (1);
}

char	*ft_strnext( char *haystack, const char *needle)
{
    int i;
    int j;
    
    i = 0;
    while (haystack && haystack[i])
    {
        j = 0;
        while (needle && needle[j] && (haystack[i + j] == needle[j]))
            j++;
        if (needle[j] == '\0')
        {
            while (haystack && (haystack [j] == '\t' || haystack[j] == ' '))
                j++;
            return (haystack + j);
        }
        i++;
    }
	return (NULL);
}

int extruct_elements(char *line)
{
    int             i;
    int             col;
    char            *str;
    char            **s_ar;
    t_elements      *element;
    
    // printf("start \n");
    i = 0;
    str = NULL;
    element = getter();
    str = ft_strnext(line, "NO");
    if (str && element->no)
        ft_error_el ("elements was duplicated");
    if (!str)
    {
        str = ft_strnext(line, "SO");
        if (str && element->so)
            ft_error_el ("elements was duplicated");
    }
    if (!str)
    {
        str = ft_strnext(line, "WE");
        if (str && element->we)
            ft_error_el ("elements was duplicated");
    }
    if (!str)
    {
        str = ft_strnext(line, "EA");
        if (str && element->ea)
            ft_error_el ("elements was duplicated");
    }
    if (!str)
    {
        str = ft_strnext(line, "F");
        if (str && element->f)
        {
            printf("--> %s :---> %zu", str, ft_strlen(str));
            ft_error_el ("elements was duplicated ************\n");
        }
        if (str)
        {
            // printf("me\n");
            element->f = malloc(sizeof(t_color));
            if (!element->f)
                ft_error_el("can not allocat");
            ft_bzero(element->f, sizeof(t_color));
            s_ar = ft_split(str, ',');
            col = 0;
            while (s_ar[col])
                col++;
            if(col != 3)
                ft_error_el("argument of coloro argb not correct\n");
            element->f->a = ft_atoi(s_ar[0]);
            element->f->b = ft_atoi(s_ar[1]);
            element->f->c = ft_atoi(s_ar[2]);
        }
    }
    if (!str)
    {
        str = ft_strnext(line, "C");
        if (str && element->c)
            ft_error_el ("elements was duplicated  -------\n");
        if (str)
        {
            element->c = malloc(sizeof(t_color));
            if (!element->c)
                ft_error_el("can not allocat");
            ft_bzero(element->c, sizeof(t_color));
            s_ar = ft_split(str, ',');
            col = 0;
            while (s_ar[col])
                col++;
            if(col != 3)
                ft_error_el("argument of coloro argb not correct\n");
            element->c->a = ft_atoi(s_ar[0]);
            element->c->b = ft_atoi(s_ar[1]);
            element->c->c = ft_atoi(s_ar[2]);
        }
    }
    while (!str && line && line[i])
    {
        if (line[i] != ' ')
            ft_error_el("invalide character\n");
        i++;   
    }
    // printf("end \n");
    return (str != NULL);
}



int extruct_them(char *line)
{
    int             i;
    char            *str;
    t_elements      *element;
    
    // printf("start \n");
    i = 0;
    str = NULL;
    element = getter();
    str = ft_strnext(line, "NO");
    if (!str)
    {
        str = ft_strnext(line, "SO");
    }
    if (!str)
    {
        str = ft_strnext(line, "WE");
    }
    if (!str)
    {
        str = ft_strnext(line, "EA");
    }
    if (!str)
    {
        str = ft_strnext(line, "F");
    }
    if (!str)
    {
        str = ft_strnext(line, "C");
    }
    while (!str && line && line[i])
    {
        if (line[i] != ' ')
            ft_error_el("invalide character\n");
        i++;   
    }
    // printf("end \n");
    return (str != NULL);
}




void    map(char **argv)
{
    int     fd;
    int     number;
    char    *line;
    t_elements  *element;

    element = getter();

    fd = open (argv[1], O_RDONLY,0644);
    line = NULL;
    line = get_next_line(fd);
    number = 0;
    while (line && (number < 6))
    {
        // printf(" ------> %s \n", line);
        number += extruct_elements(line);
        free (line);
        line = NULL;
        line = get_next_line(fd);
    }
    if (number < 6)
        ft_error_el("element or more are absents");
    start_map(line, fd);
    upload_map(argv);
    cheack_map();
    // deb_map();
    
}
