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

t_rgb *init_rgb(int r, int g, int b)
{
	t_rgb *temp;

	temp = ft_calloc(sizeof(t_rgb), 1);
	if (!temp)
		exit_error("Error malloc", 6);
	temp->r = r;
	temp->g = g;
	temp->b = b;
	return (temp);
}

t_point *init_point(float x, float y, float z)
{
	t_point *temp;

	temp = ft_calloc(sizeof(t_rgb), 1);
	if (!temp)
		exit_error("Error malloc", 6);
	temp->x = x;
	temp->y = y;
	temp->z = z;
	return (temp);
}

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

void check_less(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '-' && i != 0)
			exit_error("ERROR\nCARACTER '-' EN POSICION ERRONEA", 1);
	}
}
