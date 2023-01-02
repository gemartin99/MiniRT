/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 13:07:37 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 13:07:39 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

float	ft_atof(char *n)
{
	int		i;
	int		j;
	float	nb;
	int		m;
	
	i = 0;
	nb = 0;
	m = 1;
	j = 1;
	if (n[i] == '-')
		{
			m = -m;
			i++;
		}
	while (n[i])
	{
		if (j > 1 && n[i - 1] != '.')
			j *= 10;
		if (n[i] == '.')
			j *= 10;
		else
			nb = nb * 10 + (n[i] - 48);
		i++;
	}
	return (m * nb / j);
}

t_obj	*ft_last(t_obj **obj)
{
	t_obj	*temp;

	if (!*obj)
		return (*obj);
	temp = *obj;
	while (temp->next)
		temp = temp->next;
	return (temp);
}
