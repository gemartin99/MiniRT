/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elem2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:31:34 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 13:31:39 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

t_pd	*init_pd(char **line)
{
	t_pd	*temp;
	int		i;

	i = -1;
	while (line[++i])
		;
	temp = ft_calloc(sizeof(t_pl), 1);
	if (!temp)
		exit_error("Error malloc", 9);
	parsing_pd(line, i, temp);
	return (temp);
}

t_rgb	*init_rgb(int r, int g, int b)
{
	t_rgb	*temp;

	temp = ft_calloc(sizeof(t_rgb), 1);
	if (!temp)
		exit_error("Error malloc", 6);
	temp->r = r;
	temp->g = g;
	temp->b = b;
	return (temp);
}

t_point	*init_point(float x, float y, float z)
{
	t_point	*temp;

	temp = ft_calloc(sizeof(t_rgb), 1);
	if (!temp)
		exit_error("Error malloc", 6);
	temp->x = x;
	temp->y = y;
	temp->z = z;
	return (temp);
}
