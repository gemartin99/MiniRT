/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:53:46 by smiro             #+#    #+#             */
/*   Updated: 2023/01/02 21:53:47 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

float	sqr(float n)
{
	return (n * n);
}

float	v_len(t_point	*v)
{
	float	n;

	n = v_len2(v);
	if (n == 0)
		return (1);
	return (sqrt(n));
}

float	v_len2(t_point	*v)
{
	return (sqr(v->x) + sqr(v->y) + sqr(v->z));
}

t_point	v_sum(t_point *v1, t_point *v2)
{
	t_point	new;

	new.x = v1->x + v2->x;
	new.y = v1->y + v2->y;
	new.z = v1->z + v2->z;
	return (new);
}

t_point	v_minus(t_point	*v1, t_point *v2)
{
	t_point	new;

	new.x = v2->x - v1->x;
	new.y = v2->y - v1->y;
	new.z = v2->z - v1->z;
	return (new);
}

t_point	v_mult(t_point	*v1, float n)
{
	t_point	new;

	new.x = v1->x * n;
	new.y = v1->y * n;
	new.z = v1->z * n;
	return (new);
}
