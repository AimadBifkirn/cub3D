/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmounji <zmounji@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 16:28:16 by zmounji           #+#    #+#             */
/*   Updated: 2025/06/30 14:53:40 by zmounji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../cube.h"



int copy_map(char *line, int fd)
{
    int i;
    int j;
    t_elements      *element;
    
    element = getter();
    j = 0;
    while(line)
    {
        i = 0;
        while(line && line[i])
        {
            if (line && line[i] && line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != '\0' && line[i] != 'N' && line[i] != 'E' && line[i] != 'O' && line[i] != 'S')
            {
                ft_error_el("invalid character NOO \n");
            }
            element->map->map[j][i] = line[i];
            i++;
        }
        while (i < element->map->colomns)
        {
            element->map->map[j][i] = ' ';
            i++;
        }
        element->map->map[j][i] = '\0';
        j++;
        free (line);
        line = NULL;
        line = get_next_line(fd);
    }
    printf("bay was uploded\n");
    close (fd);
    return (1);
}

int    upload_map(char **argv)
{
    int         fd;
    int         i;
    int         ismap;
    int         number;
    char        *line;
    t_elements  *elements;

    fd = open (argv[1], O_RDONLY,0644);
    if (fd < 0)
        ft_error_el("failed fd\n");
    line = NULL;
    line = get_next_line(fd);
    number = 0;
    ismap = 0;
    elements = getter();
    while (line && (number < 6))
    {
        // printf(" ------> %s \n", line);
        if (ft_strnext(line, "NO") || ft_strnext(line, "SO") || ft_strnext(line, "WE") || ft_strnext(line, "EA") || ft_strnext(line, "F") || ft_strnext(line, "C"))
        {
            number += extruct_them(line);
        }
        if (line)
        {
            free (line);
            line = NULL;
        }
        line = get_next_line(fd);
    }
    if (number < 6)
        ft_error_el("element or more are absents");
    while (line)
   {
        i = 0;
        while(line[i])
        {
            if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            {
                ismap = 1;
                break;
            }
            i++;
        }
        if (ismap == 1)
        {
            return (copy_map(line, fd));
        }
        if (line)
        {
            free (line);
            line = NULL;
        }
        line = get_next_line(fd);
   }
   return (1);
}
