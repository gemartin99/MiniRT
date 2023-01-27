/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smiro <smiro@student.42barcelona>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 19:51:40 by smiro             #+#    #+#             */
/*   Updated: 2023/01/14 19:51:44 by smiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	check_shadow(t_intersection *i, t_ray *ray, t_obj *o)
{
	t_intersection	*tempi;
	int				res;

	tempi = new_cpy(i, sizeof(t_intersection));
	tempi->ray = ray;
	tempi->t = ray->t_max;
	res = obj_doesint(tempi, &o);
	free(ray->direction);
	free(ray->origin);
	free(ray);
	free(tempi);
	return (res);
}

int	is_shadow(t_intersection *i, t_lp *lp, t_obj *o)
{
	t_vector		v;
	t_ray			*lray;
	t_vector	a;
	lray = new_calloc(sizeof(t_ray), 1, 101);
	lray->origin = new_calloc(sizeof(t_point), 1, 102);
	*lray->origin = i_position(*i);
	v = v_minus(lray->origin, lp->lpoint);
	lray->t_max = v_len(&v);
	lray->direction = v_normalized(&v, 0);
	a = v_mult(lray->direction, 1.1);
	*lray->origin = v_sum(lray->origin, &a);
	if (check_shadow(i, lray, o))
		return (1);
	return (0);
}
