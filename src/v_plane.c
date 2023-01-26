/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:59:03 by smiro             #+#    #+#             */
/*   Updated: 2023/01/20 14:59:09 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "../inc/libft/libft.h"

t_vector	*pl_normal(t_vector *vector)
{
	t_vector	*normal;
	t_vector	*temp;

	temp = v_cross(vector2(0, 1), *vector);
	normal = v_cross(*vector, *temp);
	if (!normal->x && !normal->y && !normal->z)
		normal->x = 1;
	free(temp);
	v_normalize(&normal);
	return (normal);
}

int	pl_inter(t_intersection *i, t_obj	*o)
{
	float	dn;
	float	xv;
	float	t;
	t_pl	*plane;

	plane = new_cpy(o->elem, sizeof(t_pl));
	dn = v_dot(*i->ray->direction, *plane->normal);
	xv = v_dot(v_minus(plane->point, i->ray->origin), *plane->normal) * -1;
	if (!dn || (dn < 0 && xv > 0) || (dn > 0 && xv < 0))
	{
		free(plane);
		return (0);
	}
	t = xv / dn;
	if (t <= RAY_T_MIN || t >= i->t)
		return (0);
	i->t = t;
	i->shape = o;
	return (1);
}

int	pl_doesinter(t_intersection *i, t_obj	*o)
{
	float	dn;
	float	xv;
	float	t;
	t_pl	*plane;

	plane = new_cpy(o->elem, sizeof(t_pl));
	dn = v_dot(*i->ray->direction, *plane->normal);
	xv = v_dot(v_minus(plane->point, i->ray->origin), *plane->normal) * -1;
	if (!dn || (dn < 0 && xv > 0) || (dn > 0 && xv < 0))
	{
		free(plane);
		return (0);
	}
	t = xv / dn;
	if (t <= RAY_T_MIN || t >= i->t)
		return (0);
	return (1);
}
