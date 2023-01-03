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

#include "../../inc/minirt.h"

float	sqr(float n)
{
	return (n * n);
}

float	v_len(t_point	*v)
{
	return (sqrt(v_len2(v)));
}

float	v_len2(t_point	*v)
{
	return (sqr(v->x) + sqr(v->y) + sqr(v->z));
}

void	v_sum(t_point **v1, t_point **v2)
{
	(*v1)->x += (*v2)->x;
	(*v1)->y += (*v2)->y;
	(*v1)->z += (*v2)->z;
}

void	v_minus(t_point	**v1, t_point **v2)
{
	(*v1)->x += (*v2)->x;
	(*v1)->y += (*v2)->y;
	(*v1)->z += (*v2)->z;
}
