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

#include "../../inc/minirt.h"

t_point	r_calculate(t_ray ray, float t)
{
	return (v_sum(ray.origin, v_mult(ray.direction, t)));
}

int	i_intersected(t_intersection i)
{
	return (i.shape);
}

t_point	i_position(t_intersection i)
{
	return (r_calculate(i.ray, i.t));
}

int	obj_int(t_intersection *i, t_obj *o)
{
	t_obj	*temp;
	int		bool;

	temp = &o;
	bool = 0;
	while (temp)
	{
		if (temp->intx(i, temp->elem))
			bool = 1;
		temp = temp->next;
	}
	return (bool);
}

int	obj_doesint(t_intersection *i, t_obj *o)
{
	t_obj	*temp;

	temp = o;
	while (temp)
	{
		if (temp->doesintx(i, temp->elem))
			return (1);
		temp = temp->next;
	}
	return (0);
}

void	put_func(t_obj *obj)
{
	if (obj->id == SP)
	{
		obj->intx = &sp_inter;
		obj->doesintx = &sp_doesinter;
	}
	else if (obj->id == PL)
	{
		obj->intx = &pl_inter;
		obj->doesintx = &pl_doesinter;
	}
	else
	{
		obj->intx = NULL;
		obj->doesintx = NULL;
	}
}
