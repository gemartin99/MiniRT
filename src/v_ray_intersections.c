/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersections.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:20:18 by smiro             #+#    #+#             */
/*   Updated: 2023/01/03 13:20:20 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_point	r_calculate(t_ray ray, float t)
{
	t_point	temp;

	temp = v_mult(ray.direction, t);
	return (v_sum(ray.origin, &temp));
}

int	i_intersected(t_intersection i)
{
	if (i.shape)
		return (1);
	return (0);
}

t_point	i_position(t_intersection i)
{
	return (r_calculate(*(i.ray), i.t));
}

void	put_func(t_obj **obj)
{
	t_obj	*temp;

	temp = *obj;
	while (temp)
	{
		if (temp->id == SP)
		{
			temp->intx = &sp_inter;
			temp->doesintx = &sp_doesinter;
		}
		else if (temp->id == PL)
		{
			temp->intx = &pl_inter;
			temp->doesintx = &pl_doesinter;
		}
		else
		{
			temp->intx = &cy_inter;
			temp->doesintx = &cy_doesinter;
		}
		temp = temp->next;
	}
}
