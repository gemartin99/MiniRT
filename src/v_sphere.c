/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:02:30 by smiro             #+#    #+#             */
/*   Updated: 2023/01/20 15:02:31 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	sp_inter(t_intersection *i, t_obj	*o)
{
	t_vector	*local;
	float		n[3];
	t_sp		*sphere;

	sphere = o->elem;
	local = new_cpy(i->ray->origin, sizeof(t_point));
	*local = v_minus(sphere->point, local);
	n[0] = v_len2(i->ray->direction);
	n[1] = 2 * v_dot(*(i->ray->direction), *(local));
	n[2] = v_len2(local) - sqr(sphere->dia / 2);
	free(local);
	if (cuadratic(i, n) == -1)
		return (0);
	i->shape = o;
	return (1);
}

int	sp_doesinter(t_intersection *i, t_obj	*o)
{
	t_vector	*local;
	float		n[3];
	t_sp		*sphere;

	sphere = o->elem;
	local = new_cpy(i->ray->origin, sizeof(t_point));
	*local = v_minus(sphere->point, local);
	n[0] = v_len2(i->ray->direction);
	n[1] = 2 * v_dot(*(i->ray->direction), *(local));
	n[2] = v_len2(local) - sqr(sphere->dia / 2);
	free(local);
	if (cuadratic(i, n) == -1)
		return (0);
	return (1);
}
