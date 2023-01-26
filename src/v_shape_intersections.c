/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 14:10:06 by smiro             #+#    #+#             */
/*   Updated: 2023/01/03 14:10:09 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

int	cuadratic(t_intersection *i, float *n)
{
	int		t[2];
	float	discriminant;

	discriminant = sqr(n[1]) - 4 * n[0] * n[2];
	if (discriminant < 0)
		return (-1);
	t[0] = (-n[1] - sqrt(discriminant)) / (2 * n[0]);
	t[1] = (-n[1] + sqrt(discriminant)) / (2 * n[0]);
	if (t[0] > RAY_T_MIN && t[0] < i->t && t[0] < t[1])
		i->t = t[0];
	else if (t[1] > RAY_T_MIN && t[1] < i->t)
		i->t = t[1];
	else
		return (-1);
	n[0] = t[0];
	n[1] = t[1];
	return (0);
}

t_vector	*get_normal(t_intersection *i)
{
	t_cy		*shape;
	t_vector	temp;

	shape = i->shape->elem;
	if (i->shape->id == PL)
		return (new_cpy(((t_pl *)(shape))->normal, sizeof(t_vector)));
	else if (i->shape->id == CY)
		return (cy_normal(shape, i_position(*i)));
	temp = i_position(*i);
	temp = v_minus(&temp, shape->point);
	return (v_normalized(&temp, 0));
}

int	obj_int(t_intersection *i, t_obj **o)
{
	t_obj	*temp;
	int		bool;

	temp = *o;
	bool = 0;
	while (temp)
	{
		if (temp->intx(i, temp))
			bool = 1;
		temp = temp->next;
	}
	return (bool);
}

int	obj_doesint(t_intersection *i, t_obj **o)
{
	t_obj	*temp;

	temp = *o;
	while (temp)
	{
		if (temp->intx(i, temp))
			return (1);
		temp = temp->next;
	}
	return (0);
}
