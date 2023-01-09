/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:52:03 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 21:52:04 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

void	v_normalize(t_point **v)
{
	float	len;

	len = v_len(*v);
	(*v)->x /= len;
	(*v)->y /= len;
	(*v)->z /= len;
}

t_point	*v_normalized(t_point *v)
{
	t_point	*temp;

	temp = ft_calloc(sizeof(t_point), 1);
	if (!temp)
		exit_error("Error calloc", 15);
	temp->x = v->x;
	temp->y = v->y;
	temp->z = v->z;
	v_normalize(&temp);
	return (temp);
}

t_point	v_div(t_point	*v1, t_point *v2)
{
	v1->x += v2->x;
	v1->y += v2->y;
	v1->z += v2->z;
	return (*v1);
}

float v_dot(t_point v1, t_point v2)
{
	return (v1.x * v2.x
			+ v1.y * v2.y
			+ v1.z * v2.z);
}

t_point *v_cross(t_point v1, t_point v2)
{
	t_point	*temp;

	temp = ft_calloc(sizeof(t_point), 1);
	if (!temp)
		exit_error("Error malloc", 20);
	temp->x = v1.x * v2.z - v1.z * v2.y;
	temp->y = v1.z * v2.x - v1.x * v2.z;
	temp->z = v1.x * v2.y - v1.x * v2.x;
	return (temp);
}