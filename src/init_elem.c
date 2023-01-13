/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_elem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:31:34 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 13:31:39 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

t_sp	*init_sp(char **line)
{
	t_sp	*temp;
	int		i;

	i = -1;
	while (line[++i])
		;
	temp = ft_calloc(sizeof(t_sp), 1);
	if (!temp)
		exit_error("Error malloc", 8);
	parsing_sp(line, i, temp);
	return (temp);
}

t_pl	*init_pl(char **line)
{
	t_pl	*temp;
	int		i;

	i = -1;
	while (line[++i])
		;
	temp = ft_calloc(sizeof(t_pl), 1);
	if (!temp)
		exit_error("Error malloc", 9);
	parsing_pl(line, i, temp);
	return (temp);
}

t_cy	*init_cy(char **line)
{
	t_cy	*temp;
	int		i;

	i = -1;
	while (line[++i])
		;
	temp = ft_calloc(sizeof(t_cy), 1);
	if (!temp)
		exit_error("Error malloc", 8);
	parsing_cy(line, i, temp);
	return (temp);
}
