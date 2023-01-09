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

int	pl_inter(t_intersection *i, t_obj	*o)
{
	float	dn;
	float	t;
	t_pl	*plane;

	plane = o->elem;
	dn = v_dot(*i->ray->direction, *plane->vector);
	if (!dn)
		return (0);
	t = v_dot(v_minus(plane->point, i->ray->origin), *plane->vector) / dn;
	if (t <= RAY_T_MIN || t >= i->t)
		return (0);
	i->t = t;
	i->shape = o;
	return (1);
}

int	pl_doesinter(t_intersection *i, t_obj	*o)
{
	float	dn;
	float	t;
	t_pl	*plane;

	plane = o->elem;
	dn = v_dot(*i->ray->origin, *plane->vector);
	if (!dn)
		return (0);
	t = v_dot(v_minus(plane->point, i->ray->origin), *plane->vector);
	if (t <= RAY_T_MIN || t >= i->t)
		return (0);
	return (1);
}

int	sp_inter(t_intersection *i, t_obj	*o)
{
	t_ray	*localray;
	float	n[3];
	float	discriminant;
	float	t[2];
	t_sp	*sphere;

	sphere = o->elem;
	localray = new_calloc(sizeof(t_ray), 1, 30);
	ft_memcpy(localray, i->ray, sizeof(t_ray));
	localray->origin = new_calloc(sizeof(t_vector), 1, 31);
	ft_memcpy(localray->origin, i->ray->origin, sizeof(t_vector));
	localray->direction = new_calloc(sizeof(t_vector), 1, 32);
	ft_memcpy(localray->direction, i->ray->direction, sizeof(t_vector));
	v_minus(localray->origin, sphere->point);
	n[0] = v_len2(localray->direction);
	n[1] = 2 * v_dot(*localray->direction, *localray->origin);
	n[2] = v_len2(localray->origin) - sqr(sphere->dia / 2);
	discriminant = sqr(n[1]) - 4 * n[0] * n[2];
	free(localray->origin);
	free(localray->direction);
	free(localray);
	if (discriminant < 0)
		return (0);
	t[0] = (-n[1] - sqrt(discriminant)) / (2 * n[0]);
	t[1] = (-n[1] + sqrt(discriminant)) / (2 * n[0]);
	if (t[0] > RAY_T_MIN && t[0] < i->t)
		i->t = t[0];
	else if (t[1] > RAY_T_MIN && t[1] < i->t)
		i->t = t[1];
	else
		return (0);
	i->shape = o;
	return (1);
}

int	sp_doesinter(t_intersection *i, t_obj	*o)
{
	t_ray	*localray;
	float	n[3];
	float	discriminant;
	float	t[2];
	t_sp	*sphere;

	sphere = o->elem;
	localray = i->ray;
	v_minus(localray->origin, sphere->point);
	n[0] = v_len2(localray->direction);
	n[1] = 2 * v_dot(*localray->direction, *localray->origin);
	n[2] = v_len2(localray->origin) - sqr(sphere->dia / 2);
	discriminant = sqr(n[1]) - 4 * n[0] * n[2];
	if (discriminant < 0)
		return (0);
	t[0] = (-n[1] - sqrt(discriminant)) / (2 * n[0]);
	if (t[0] > RAY_T_MIN && t[0] < i->t)
		return (1);
	t[1] = (-n[1] + sqrt(discriminant)) / (2 * n[0]);
	if (t[1] > RAY_T_MIN && t[1] < i->t)
		return (1);
	return (0);
}
